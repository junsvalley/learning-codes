#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global;

int main ()
{
    int local = 5;
    void *p = malloc(1024);

    void *pb = sbrk(0);

    //void *p2 = malloc(1024*132); //131 small, 132 large

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);
    printf ("Address of program break is %p, len 0x%x\n", pb, pb-p );
    //printf ("Address of p2 is %p\n", p2);
}
