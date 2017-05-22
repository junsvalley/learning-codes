#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t cpid; //child pid
    FILE *fd = popen("arp -n", "r");

    if(!fd) fprintf(stderr, "Error happened...\n");
    
    char line[100]={0};
    while(fgets(line, 100, fd))
    {
       //printf("recv - %s", line);
       fputs(line, stdout);
       fflush(stdout);
    }
    pclose(fd);
    return 0;
}


