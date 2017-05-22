#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#define MYSIZE 1024

int main()
{
    key_t k = ftok("/home/gufeng/codes/process/shmkfile", 'a');
    int shmid = shmget(k, MYSIZE, IPC_CREAT);
    printf("key is 0x%x shmid is %d\n", k, shmid);
    char *shmaddr = NULL;
    char buf[MYSIZE] = {0};
    if(shmid >0)
    {
      shmaddr = (char*)shmat(shmid, NULL, 0);
      printf("share memory address is %p\n", shmaddr);
      memcpy(buf, shmaddr, MYSIZE);
      printf("received message [%s]\n", buf);
      shmdt(shmaddr);
      shmctl(shmid, IPC_RMID, 0);
    }

    return 0;
}


