#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    char buf[100]={0};
    int len=0;
    int fd = open("/home/gufeng/codes/process/myfifo", O_CREAT | O_WRONLY | O_NONBLOCK);
    if (fd < 0 )
    {
        fprintf(stderr, "Open failed!!!\n");
        exit(-1);
    }
    while(1)
    {
        fgets(buf, 100, stdin);    
        len = strlen(buf);
        write(fd, buf, len); 
    }

    return 0;
}


