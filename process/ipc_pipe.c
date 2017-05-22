#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t cpid; //child pid
    char buf[100]={0};
    int fd[2];
    int status;
    if(pipe(fd)<0)
        fprintf(stderr, "pipe create error!!!\n");

    cpid=fork();
    if(cpid>0){
       close(fd[0]);
       write(fd[1], "Hello, GU Feng :)", 18);
       close(fd[1]);
       wait(&status);
       printf("parent process - child pid is %d\n", cpid);
       exit(0);
    }else if(cpid==0){
       close(fd[1]);
       read(fd[0], buf, 100);
       close(fd[0]);
       printf("child process, %s\n", buf);
    }else{
       printf("error happened!!!\n");
    }
    return 0;
}


