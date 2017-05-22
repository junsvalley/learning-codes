#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g = 12306;

void fork_test()
{
    pid_t cpid; //child pid
    cpid=fork();
    if(cpid>0){
       g++;
       printf("parent process - child pid is %d, g = %d\n", cpid, g);
       exit(0);
    }else if(cpid==0){
       g+=20;
       printf("child process %d\n", g);
    }else{
       printf("error happened!!!\n");
    }
}

void vfork_test()
{
    pid_t cpid; //child pid
    cpid=vfork(); //make sure the child process execute firstly
    if(cpid>0){
       g++;
       printf("vfork parent process - child pid is %d, g = %d\n", cpid, g);
    }else if(cpid==0){
       g+=20;
       printf("vfork child process %d\n", g);
       /*
        * after child process, shall recall the parent process  
        * segment fault if not exit  
        */
       exit(0); //_exit(0)
    }else{
       printf("vfork - error happened!!!\n");
    }
}

void fork_wait_test()
{
    pid_t cpid; //child pid
    cpid=fork();
    if(cpid>0){
       g++;
       if(waitpid(cpid, NULL, 0)!=cpid)//if waitpid(-1,NULL,0) wait all child process
           fprintf(stderr, "waitpid error!!!");
       printf("parent process - child pid is %d, g = %d\n", cpid, g);
    }else if(cpid==0){
       g+=20;
       printf("child process %d - getppid %d\n", g, getppid());
       sleep(2);
       exit(0);
    }else{
       printf("error happened!!!\n");
    }
}
int main()
{
    fork_test();
    //vfork_test();
    //fork_wait_test();
    return 0;
}


