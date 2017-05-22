#include <arpa/inet.h>
#include <stdio.h>
#include <sys/mman.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  

union maddr{
    unsigned int addr;
    unsigned char c[4];
};

int main()
{
    union maddr a;
    a.addr = 0x11110000;
    unsigned int naddr = htonl(a.addr);
    void *ptr = 0;
    printf("0x%x to 0x%x, sizeof pointer is %d, sizeof long %d\n", a.addr, naddr, sizeof(ptr), sizeof(long));
    printf("0x%x 0x%x 0x%x 0x%x\n", a.c[0], a.c[1],a.c[2],a.c[3]);
  
#define BUF_SIZE 100  
  
    char    *p_map;  
    int pagesize = sysconf(_SC_PAGESIZE);  
    printf("pagesize is %d\n",pagesize);  

  
    p_map = (char *)mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE,  
            MAP_SHARED | MAP_ANONYMOUS, -1, 0);  
  
    if(fork() == 0) {  
        sleep(1);  
        printf("child got a message: %s\n", p_map);  
        sprintf(p_map, "%s", "hi, dad, this is son");  
        munmap(p_map, BUF_SIZE);
        exit(0);  
    }  
  
    sprintf(p_map, "%s", "hi, this is father");  
    sleep(2);  
    printf("parent got a message: %s\n", p_map);  
  
    return 0;
}
