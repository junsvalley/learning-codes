#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#define MYSIZE 1024
char swords[1024] = {0};

int main()
{
    key_t k = ftok("/home/gufeng/codes/process/shmkfile", 'a');
    //int shmid = shmget(IPC_PRIVATE, MYSIZE, IPC_CREAT|0600);
    int shmid = shmget(k, MYSIZE, IPC_CREAT);
    printf("key is 0x%x shmid is %d\n", k, shmid);
    char* shmaddr;
    if(shmid >0)
    {
      shmaddr = (char*) shmat(shmid, NULL, 0);
      shmat(shmid, swords, 0);
      char words[MYSIZE] = {0};
      strcpy(words, "Hi i am xx, it's my honor to be here to have this ineterview, I have 8 years work experience since I graduated from the university.");
      printf("share memory address is %p, %p\n", shmaddr, swords);
      strcpy(shmaddr, words);
      printf("%s\n", shmaddr);
      sleep(50);
      shmdt(shmaddr);
      shmctl(shmid, IPC_RMID, 0);
    }

    return 0;
}


