#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <netinet/tcp.h>
#include "high_concurrency.h"

int create_client_socket()
{
  int fd;
  CHK_OK(fd = socket(AF_INET, SOCK_STREAM, 0));
  return fd;
}

void connect_to_server(int fd)
{
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  /* inet_addr(SERVER_ADDR) */
  inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr.s_addr);
  server_addr.sin_port = htons(SERVER_PORT);
  CHK_OK(connect(fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)));
}

void send_req_msg(int fd)
{
  int len;
  char buf[SND_BUFSIZ] = {0};
  snprintf(buf, SND_BUFSIZ, "HC server!!! Heard a lot about you, nice to meet you, I am %d", fd);
  len = send(fd, buf, strlen(buf), 0);
  if(len == -1) close(fd); /* server already closed */
}

void recv_res_msg(int fd)
{
  int len;
  char buf[RCV_BUFSIZ] = {0};
  CHK_OK(len = recv(fd, buf, RCV_BUFSIZ, 0));
  if(len == 0)
  {
    HC_PRINT("close socket %d\n", fd);
    close(fd); /* server already closed */
  } else
    HC_PRINT("%s\n", buf);
}

int main()
{
  int i=0;
  int fd[SERVER_CAPACITY] = {0};
  struct pollfd set[SERVER_CAPACITY];

  for(; i<SERVER_CAPACITY; i++)
  {
    fd[i] = create_client_socket();
    connect_to_server(fd[i]); 

    set[i].fd = fd[i];
    set[i].events = POLLOUT;
    set[i].revents = 0;
  }

  while(TRUE)
  {
    if(poll(set, sizeof(set)/sizeof(*set), -1) < 0)
      continue;
      
    for(i=0; i<SERVER_CAPACITY; i++)
    {
      if(set[i].revents & POLLOUT)
        send_req_msg(fd[i]);
 
      if(set[i].revents & POLLIN)
        recv_res_msg(fd[i]);

      /* clean revents & always set POLLIN */
      set[i].fd = fd[i];
      set[i].events = POLLIN;
      set[i].revents = 0;
    }
  }

  for(i=0; i<SERVER_CAPACITY; i++)
  {
    close(fd[i]);
  }
  return 0;
}
