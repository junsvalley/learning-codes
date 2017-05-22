#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t cpid; //child pid
    char buf[100]={0};
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    cpid = fork();
    if(cpid>0){
        close(pipe1[1]); //index 1 is write tunnel
        close(pipe2[0]); //index 0 is read tunnel
        write(pipe2[1], "parent write something\n", 30);
        char buf[100]={0};
        read(pipe1[0], buf, 100);
        fputs(buf, stdout);
        close(pipe1[0]);
        close(pipe2[1]);
    }else{
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], "child write something\n", 30);
        char buf[100]={0};
        read(pipe2[0], buf, 100);
        fputs(buf, stdout);
        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}


