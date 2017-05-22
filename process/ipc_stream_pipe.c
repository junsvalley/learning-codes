#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int s_pipe(int fd[2])
{
    return socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
}

int main()
{
    pid_t cpid; //child pid
    char buf[100]={0};
    int fd[2];
    int status;
    //if(s_pipe(fd)<0)
    if( socketpair(AF_UNIX, SOCK_STREAM, 0, fd)<0)
        fprintf(stderr, "stream pipe create error!!!\n");

    cpid=fork();
    if(cpid>0){ //parent only use fd[0]
       close(fd[1]);

       write(fd[0], "Hello, GU Feng :)", 18);
       printf("parent connected with child(%d)\n", cpid);
       sleep(2);

       read(fd[0], buf, 100);
       printf("parent print - child said:\"%s\"\n", buf);

       close(fd[0]);
       wait(&status); //wait child process exit
    }else if(cpid==0){ //child only use fd[1]
       close(fd[0]);

       sleep(1);
       read(fd[1], buf, 100);
       printf("child print - parent said:\"%s\"\n", buf);

       write(fd[1], "Hello, I am here ^v^", 20);

       close(fd[1]);
    }else{
       printf("error happened!!!\n");
    }

    return 0;
}


