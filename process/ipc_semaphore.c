#include<stdio.h>  
#include<unistd.h>  
//#include<semaphore.h>
#include<sys/sem.h>  
//#include<linux/sem.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>  
#include<error.h>  
#include<pthread.h>
#include<assert.h>
#include<sys/syscall.h>

#define gettid() syscall(__NR_gettid)
#define MAX_SRC_NUM 0
struct msem_info {
    int sem_id;
};

void sem_request(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; //negative for resource request
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sem_b, 1) == -1){
	printf("semop failure!!!\n");
	exit(-1);
    }
}

void sem_release(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; //positive for resource release
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sem_b, 1) == -1){
	printf("semop failure!!!\n");
	exit(-1);
    }
}

void* sem_process(void *param)
{
    struct msem_info *sinfo = (struct msem_info*)param;
    int sem_id = sinfo->sem_id;
 
    sem_request(sem_id);
    printf("%ld - requested one source.\n", gettid());
    /*
     * do something for shareing resources, such as share memory etc.
     */
    sleep(5);
    sem_release(sem_id);
    printf("%ld - released one source.\n", gettid());

    sleep(3);

}

int main(){  
    int *share;  
    int num;  
    //srand(time(NULL));  
    int sem_id;  
    sem_id = semget (1234, MAX_SRC_NUM, IPC_CREAT);  
    if(sem_id == -1){  
	perror("semget()");  
    }
    //union semun sem_union;
    //sem_union.val = 1;
    if(semctl(sem_id, 0, SETVAL, 1) == -1) exit(-1);

    pthread_t pid[2];
    struct msem_info sinfo;
    sinfo.sem_id = sem_id;
    if(pthread_create(&pid[0], 0, sem_process, (void*)&sinfo) < 0)
        assert(0);
    if(pthread_create(&pid[1], 0, sem_process, (void*)&sinfo) < 0)
        assert(0);

    sleep(100);
    if(semctl(sem_id, 0, IPC_RMID, 0)==-1)exit(-1);
    return 0;  
}

