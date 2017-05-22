#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#define FU_SERVER_PORT 9901 /*set port*/
#define FU_BUFFERSIZE 1024 /*set buffer size*/
#define FU_LISTENQ 10   /*set listen max conncent*/

int main(int argc, char *argv[])
{
    int fu_listenfd, fu_connfd, fu_filefd; /*descriptor*/
    int fu_read, fu_write;
    int struct_size;
    struct sockaddr_in fu_servaddr, fu_cliaddr;
    char *fu_filename;
    char *p;
    char buffer[FU_BUFFERSIZE];

    fu_listenfd = socket(AF_INET, SOCK_STREAM, 0); /*create socket*/
    if(fu_listenfd == -1)
    {
        perror("fu_socket");
        exit(1);
    }
    memset(&fu_servaddr, 0, sizeof(fu_servaddr)); /*servaddr set 0*/

    fu_servaddr.sin_family = AF_INET;  /*init serveraddr*/
    fu_servaddr.sin_addr.s_addr = INADDR_ANY;
    fu_servaddr.sin_port = htons(FU_SERVER_PORT);

    /*bind fu_listenfd*/

    if(-1 == (bind(fu_listenfd, (struct sockaddr *)&fu_servaddr, sizeof(fu_servaddr))))
    {
        perror("fu_bind");
        exit(1);
    }
    /*listen fu_listenfd*/
    if(-1 == (listen(fu_listenfd, FU_LISTENQ)))
    {
        perror("fu_listen");
        exit(1);
    }

    /*file upload server start*/
    while(1)
    {
        printf("file upload server starting......\n");

        memset(&fu_cliaddr, 0, sizeof(fu_cliaddr));
        struct_size = sizeof(fu_cliaddr);

        fu_connfd = accept(fu_listenfd, (struct sockaddr *)&fu_cliaddr, (socklen_t*)&struct_size);
        if(-1 == fu_connfd)
        {
            perror("fu_accpet");
            continue;
        }

        char fNameBuf[100]={0};
        //get file name firstly
        if ( read(fu_connfd, fNameBuf, sizeof(fNameBuf)) < 0 )
        {
            perror("read file name error");
            exit(1);
        }

        snprintf(fu_filename, strlen(fNameBuf)+1, "%s", fNameBuf);
        printf("will store the upload file to this file :%s\n", fu_filename);

        fu_filefd = open(fu_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if (fu_filefd < 0)
        {
            perror("open localhost file");
            continue;
        }

        while(fu_read = read(fu_connfd, buffer, FU_BUFFERSIZE))
        {
            if (fu_read < 0)
            {
                perror("read client file");
                break;
            }
            if (-1 == write(fu_filefd, buffer, fu_read))
            {
                perror("writing to filefd error");
                break;
            }
        }
        if(-1 == fu_read || -1 == fu_write) continue;
        close(fu_filefd);
        close(fu_connfd);
        printf("file upload success!\n");
    }
    close(fu_listenfd);
    return 0;
}
