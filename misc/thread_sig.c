#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void interrupt_handler(int signo)
{
  printf("------< start to process %d >------\n", signo);
  sleep(10);
  printf("------< end >------\n");
  exit(0);
}

void *my_thread(void *ptr)
{
  signal(SIGINT, interrupt_handler);
  static int t=0;
  while(1)
  {
    printf("--->elasped %d\n", t++);
    sleep(1);
  }
}


int main()
{


  pthread_t pid;
  pthread_create(&pid, 0, my_thread, NULL);
   


  //pthread_join(pid, NULL);
  sleep(100);

  return 0;
}

