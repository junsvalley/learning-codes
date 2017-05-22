#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

sem_t semaphore;

void signal_catcher(int sig)
{
    sem_post(&semaphore);
}

void *sem_waiter(void *arg)
{
    int number = (int)arg;
    int counter;

    // Each thread waits 5 times.
    for(counter = 1; counter <= 5; counter++){
	while(sem_wait(&semaphore) == -1){
	    if(errno != EINTR)
		perror("Wait on semaphore");
	}
	printf("%d waking (%d)...\n", number, counter);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int thread_count;
    struct sigevent   sig_event;
    struct sigaction  sig_action;
    struct itimerspec timer_val;
    sigset_t  sig_mask;
    timer_t   timer_id;
    pthread_t sem_waiters[5];

    sem_init(&semaphore, 0, 0);

    // Create 5 threads to wait on a semaphore.
    for(thread_count = 0; thread_count < 5; thread_count++){
	pthread_create(&sem_waiters[thread_count], NULL, sem_waiter, (void *)thread_count);
    }

    /*
     * Set up a repeating timer using signal number SIGRTMIN,
     * set to occur every 2 seconds.
     */
    sig_event.sigev_value.sival_int = 0;
    sig_event.sigev_signo = SIGRTMIN;
    sig_event.sigev_notify = SIGEV_SIGNAL;
    if(timer_create(CLOCK_REALTIME, &sig_event, &timer_id) == -1)
	perror("Create timer");

    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGRTMIN);
    sig_action.sa_handler = signal_catcher;
    sig_action.sa_mask = sig_mask;
    sig_action.sa_flags = 0;
    if(sigaction(SIGRTMIN, &sig_action, NULL) == -1)
	perror("Set signal action");

    timer_val.it_interval.tv_sec = 2;
    timer_val.it_interval.tv_nsec = 0;
    timer_val.it_value.tv_sec = 2;
    timer_val.it_value.tv_nsec = 0;
    if(timer_settime(timer_id, 0, &timer_val, NULL) == -1)
	perror("Set timer");

    // Wait for all threads to complete.
    for(thread_count = 0; thread_count < 5; thread_count++){
	pthread_join(sem_waiters[thread_count], NULL);
    }
    return 0;
}
