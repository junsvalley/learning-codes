#include <stdio.h>
#include <time.h>                          
#include <sys/time.h>                      
#include <stdlib.h>                        
#include <signal.h>                        

enum addr_confd_ip_types
{
    IPTYPE_UNSET=0,
    IPTYPE_IPV4,
    IPTYPE_IPV6
};
                                           
#define XPATH_IPV4_ADDR_BLOCK   "/address-pools/address-pool[%d]/address-pool-entries/ipv4-address-block"
#define XPATH_IPV6_ADDR_BLOCK   "/address-pools/address-pool[%d]/address-pool-entries/ipv6-address-block"

/* MACO FOR BOTH IPV4 AND IPV6 AS PER IP TYPE */
#define XPATH_ADDR_BLOCK(IPTYPE) XPATH_##IPTYPE##_ADDR_BLOCK
#define XPATH_ADDR_BLOCK2(IPTYPE) ((IPTYPE==IPTYPE_IPV4)?XPATH_ADDR_BLOCK(IPV4):XPATH_ADDR_BLOCK(IPV6))

int a_a(int t)
{
    printf("%s\n", XPATH_ADDR_BLOCK2(t));
}

void entiry(void **e)
{
  *e=malloc(64);
  printf("2-%p\n", *e);
}
#define WCONFD_CONF "/usr/local/etc/certus/confd_ip.conf"
#define MAX_LINE_LEN 512


static char *get_ipv4(char *ip, int bufsize)
{
    FILE *fp = NULL;
    char line[MAX_LINE_LEN] = {0};
    char *end = NULL;

    fp = fopen(WCONFD_CONF, "rb");
    if (fp == NULL)
        return NULL;

    memset(ip, 0, bufsize);
    while(fgets(line, sizeof(line) - 1, fp) != NULL)
    {
printf("--->line %s\n", line);
        //len(1.2.3.4) == 7, min len
        if (strlen(line) < 7) // invalid ip addr
            continue;

        strncpy(ip, line, bufsize);
    }

    if (strlen(ip) == 0)
        return NULL;

    return ip;
}

int main()                                 
{                                          
    int t = IPTYPE_IPV4;
    //#printf("%s\n", XPATH_ADDR_BLOCK(a));
    printf("%s\n", XPATH_ADDR_BLOCK2(t));
    a_a(t);
    t = IPTYPE_IPV6;
    printf("%s\n", XPATH_ADDR_BLOCK2(t));
    a_a(t);

    void *e = NULL;
  printf("1-%p\n", e);
    entiry(&e);
  printf("3-%p\n", e);


   int iplen = 26;
   int ipaddr = 0;
   int i=0;
   while(i<iplen)
   {
     ipaddr |= 1<<i;
     i++;
   }
   ipaddr = ipaddr << (32-iplen);
   printf("0x%x\n", ipaddr);


    char ip[16] = {0};
  printf("--------> IP ADDRESS %s\n", get_ipv4(ip, sizeof(ip)));


    char *xpath = "/a/b{k1 k2}/c";
    char *dx = strdup(xpath);
    char *xnode = strtok(dx, "/{} ");

    while(xnode) {
      printf("--->xnode: %s\n", xnode);
      xnode = strtok(NULL, "/{} ");
    }

    return 1;                              
}                                          
