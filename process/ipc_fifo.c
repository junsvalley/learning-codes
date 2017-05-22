#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define MYFIFO_FILE "/root/codes/process/myfifo"

int main()
{
    char buf[100]={0};
    int len=0;
    int res = mkfifo(MYFIFO_FILE, S_IRWXU);
    if(res<0 && errno != EEXIST) exit(-1);

    int fd = open(MYFIFO_FILE, O_RDONLY | O_NONBLOCK);
    if(fd<0) exit(-1);

    while(1)
    {
        len = read(fd, buf, 100);
        if(len<0 && errno == EAGAIN)
            fprintf(stderr, "No data left...\n");
        
        if(len>=0)
            write(STDOUT_FILENO, buf, len);
    }

    unlink(MYFIFO_FILE); //mkfifo,unlink

    return 0;
}


