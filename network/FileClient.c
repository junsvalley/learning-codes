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

int main(int argc, char *argv[])
{
    int fu_sockfd, fu_filefd; /*descriptor*/
    int fu_read, fu_write;
    int struct_size;
    struct sockaddr_in fu_sockaddr;
    char *fu_filename;
    char *p;
    char buffer[FU_BUFFERSIZE];

    if (argc != 2)
    {
        //perror("fu_Usage: <./client> <server IP>\n");
        perror("fu_Usage: <./client> <uploaded file name>\n");
        exit(1);
    }
    fu_sockfd = socket(AF_INET, SOCK_STREAM, 0); /*create socket*/
    if(fu_sockfd == -1)
    {
        perror("fu_socket");
        exit(1);
    }

    memset(&fu_sockaddr, 0, sizeof(fu_sockaddr)); /*servaddr set 0*/

    fu_sockaddr.sin_family = AF_INET;  /*init serveraddr*/
    //inet_aton(argv[1], &fu_sockaddr.sin_addr);
    inet_aton("172.16.45.150", &fu_sockaddr.sin_addr);
    fu_sockaddr.sin_port = htons(FU_SERVER_PORT);

    if(-1 == (connect(fu_sockfd, (struct sockaddr *)&fu_sockaddr, sizeof(fu_sockaddr))))
    {
        perror("fu_connect");
        exit(1);
    }
    printf("start connecting..........\n");

    //fu_filename = "./FileClient.c";
    fu_filename = argv[1];
    printf("will upload file name is:%s\n", fu_filename);
    fu_filefd = open(fu_filename, O_RDONLY);
    if(-1 == fu_filefd)
    {
        perror("open will upload file");
        exit(1);
    }

    char fNameBuf[100]={0};
    snprintf(fNameBuf, sizeof(fNameBuf), "%s", fu_filename);
    //transfer file name firstly
    if ( write(fu_sockfd, fNameBuf, sizeof(fNameBuf)) == -1 )
    {
        perror("write file name err");
        exit(1);
    }

    while(fu_read = read(fu_filefd, buffer, FU_BUFFERSIZE))
    {
        if(-1 == fu_read)
        {
            perror("read will upload file");
            exit(1);
        }

        p = buffer;
        while(fu_write = write(fu_sockfd, p, fu_read))
        {
            if(-1 == fu_write)
            {
                perror("write client file");
                break;
            }
            else if(fu_read == fu_write) break;
            else if(fu_write > 0)
            {
                p += fu_write;
                fu_read -= fu_write;
            }
        }
        if(-1 == fu_write) exit(1);
    }

    close(fu_filefd);
    close(fu_sockfd);
    printf("file already is uploaded!\n");

}
