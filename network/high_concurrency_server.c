#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <netinet/tcp.h>
#include "high_concurrency.h"

struct client_info {
  int csock;
  struct sockaddr_in caddr;
};

struct server_info {
  int ssock;
  struct sockaddr_in saddr;
  int epollfds[SERVER_MAX_HANDLER];
  pthread_mutex_t lock;
  pthread_cond_t notify;
};

void server_socket_create(struct server_info *sinfo)
{
  CHK_OK(sinfo->ssock = socket(AF_INET, SOCK_STREAM, 0));
}

void server_socket_setopt(struct server_info *sinfo)
{
  int reuse = TRUE;
  CHK_OK(setsockopt(sinfo->ssock, SOL_SOCKET, SO_REUSEADDR, (const void*)&reuse, sizeof(int)));

  struct timeval sndtimeout = { .tv_sec = 1, .tv_usec = 0 };
  struct timeval rcvtimeout = { .tv_sec = 1, .tv_usec = 0 };
  CHK_OK(setsockopt(sinfo->ssock, SOL_SOCKET, SO_SNDTIMEO, (const void*)&sndtimeout, sizeof(struct timeval)));
  CHK_OK(setsockopt(sinfo->ssock, SOL_SOCKET, SO_RCVTIMEO, (const void*)&rcvtimeout, sizeof(struct timeval)));

  int sndbuf = 1024; //deafult is 8k if not set
  int rcvbuf = 1024; //no copy to kernal if set 0
  CHK_OK(setsockopt(sinfo->ssock, SOL_SOCKET, SO_SNDBUF, (const void*)&sndbuf, sizeof(int)));
  CHK_OK(setsockopt(sinfo->ssock, SOL_SOCKET, SO_RCVBUF, (const void*)&rcvbuf, sizeof(int)));

  int defertime = 5; //5 seconds
  int corkon = TRUE;
  CHK_OK(setsockopt(sinfo->ssock, IPPROTO_TCP, TCP_DEFER_ACCEPT, (const void*)&defertime, sizeof(int)));
  CHK_OK(setsockopt(sinfo->ssock, IPPROTO_TCP, TCP_CORK, (const void*)&corkon, sizeof(int)));
}

void server_socket_bind(struct server_info *sinfo)
{
  struct sockaddr_in *server_addr = &sinfo->saddr;
  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = INADDR_ANY;
  /* inet_addr(SERVER_ADDR) */
  inet_pton(AF_INET, SERVER_ADDR, &server_addr->sin_addr.s_addr);
  server_addr->sin_port = htons(SERVER_PORT);

  /* STREAM:
     TCP - SOCK_STREAM
     UDP - SOCK_DGRAM
     RAW - SOCK_RAW
     ...

     PROTOCOL:
     undefined - 0
     TCP - IPPROTO_TCP
     UDP - IPPROTO_UDP
     SCTP - IPPROTO_SCTP
     TIPC - IPPROTO_TIPC
     ...
   */
  CHK_OK(bind(sinfo->ssock, (struct sockaddr*)&sinfo->saddr, sizeof(struct sockaddr)));
}

void server_socket_listen(struct server_info *sinfo)
{
  CHK_OK(listen(sinfo->ssock, SERVER_CAPACITY));
}

int server_socket_accept(struct server_info *sinfo)
{
  int accept_fd;
  struct sockaddr_in remoteaddr;
  int addrlen = sizeof(&remoteaddr);
  CHK_OK(accept_fd = accept(sinfo->ssock, (struct sockaddr*)&remoteaddr, &addrlen));
  int flags = fcntl(accept_fd, F_GETFL, 0);
  fcntl(accept_fd, F_SETFL, flags | O_NONBLOCK);
  return accept_fd;
}

void recv_req_msg(int fd)
{
  int len;
  char buffer[RCV_BUFSIZ] = {0};
  CHK_OK(len = recv(fd, buffer, RCV_BUFSIZ, 0));
  if(len == 0)
  {
    close(fd); /* client already closed */
    HC_PRINT("close client socket %d\n", fd);
  }
  else
    HC_PRINT("receive len %d, %s\n", len, buffer);
}

void send_res_msg(int fd)
{
  int len;
  char buf[SND_BUFSIZ] = {0};
  snprintf(buf, SND_BUFSIZ, "Nice to meet you, Mr. %d, welcome to HC world!", fd);
  len = send(fd, buf, strlen(buf), 0/*flags*/);
  if(len == -1) close(fd); /* client already closed */
}

void *client_handler(void *param)
{
  int epollfd = (int)param;
  HC_PRINT("new epollfd %d\n", epollfd);
  while(TRUE)
  {
    struct epoll_event events[SERVER_MAX_EPOLLEVENTS];
    struct epoll_event ev;
    int numevs = epoll_wait(epollfd, events, SERVER_MAX_EPOLLEVENTS, SERVER_EPOLL_WAITTIMEOUT);
    int i = 0;
    for(; i<numevs; i++)
    {
      if(events[i].events & EPOLLIN)
      {
        recv_req_msg(events[i].data.fd);
        ev.data.fd = events[i].data.fd;
        ev.events = EPOLLOUT | EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_MOD, ev.data.fd, &ev); 
      }
      else if(events[i].events & EPOLLOUT)
      {
        send_res_msg(events[i].data.fd);
        ev.data.fd = events[i].data.fd;
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_MOD, ev.data.fd, &ev); 
      }
    }
  }
}

void server_add_clientfd(struct server_info *sinfo, int fd)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = EPOLLIN | EPOLLET;

  /* assigned to the specific epoll habdler */
  int idx = fd % SERVER_MAX_HANDLER;
  int epollfd = sinfo->epollfds[idx];
  if(epollfd == 0)
  {
    epollfd = sinfo->epollfds[idx] = epoll_create(SERVER_EPOLL_CAPACITY);
    pthread_t tid;
    CHK_OK(pthread_create(&tid, NULL, &client_handler, (void*)epollfd));
  }
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

int main()
{
  struct server_info sinfo;
  memset(&sinfo, 0, sizeof(sinfo));
  pthread_mutex_init(&sinfo.lock, NULL);
  pthread_cond_init(&sinfo.notify, NULL);
  server_socket_create(&sinfo);
  server_socket_setopt(&sinfo);
  server_socket_bind(&sinfo);
  server_socket_listen(&sinfo);

  struct timeval wait_timeout = { .tv_sec = 1, .tv_usec = 0 };
  fd_set server_read;
  int ret;
  while(TRUE)
  {
    FD_ZERO(&server_read);
    FD_SET(sinfo.ssock, &server_read);
  
    ret = select(sinfo.ssock + 1, &server_read, NULL, NULL, &wait_timeout);
    if(ret == -1)
    {
      HC_PRINT("select return with error - %s\n", strerror(errno));
      break;
    }
    else if(ret == 0)
    {
      //HC_PRINT("Wait timeout for server socket!!!\n");
      continue;
    }

    if(FD_ISSET(sinfo.ssock, &server_read))
    {
      int fd = server_socket_accept(&sinfo);
      if(fd != -1)
      {
        HC_PRINT("accept client fd %d\n", fd);
        server_add_clientfd(&sinfo, fd);
      }
    }
  }
  return 0;
}
