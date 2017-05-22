#include <stdio.h>
#include <time.h>                          
#include <sys/time.h>                      
#include <stdlib.h>                        
#include <string.h>                        
#include <signal.h>                        
#include "util.h"

#if 0
typedef struct wconfd_xpath_keys {
    char pname[16][32];
    char keys[16][32];
    int keys_num;
}wconfd_xpath_keys_t;

void wconfd_get_keys_from_xpath(const char *xpath, wconfd_xpath_keys_t *xkeys)
{
    char *pos1, *pos2, *listname;
    if((pos1 = COS_STRCHR(xpath, '{')) != NULL)
    {
        char *listpath = strdup(xpath);
        listpath[pos1 - xpath] = '\0';
        strcpy(xkeys->pname[xkeys->keys_num], listpath);
        free(listpath);

        pos2 = COS_STRCHR(pos1, '}');
        strncpy(xkeys->keys[xkeys->keys_num++], pos1 + 1, pos2 - (pos1 + 1));
        wconfd_get_keys_from_xpath(pos2+1, xkeys);
    }
}

void resolve_keys(const char *xpath, wconfd_xpath_keys_t *xkeys)
{
  printf("%s\n", xpath);
  int i=0;
  char *a = malloc(1024);
  int len=0;
  int xlen=strlen(xpath);
  int total=strlen(xpath);
       printf("xlen ---> %d\n", xlen);

  for(;i<xkeys->keys_num;i++)
  { 
     printf("************* -> %s\n", xkeys->pname[i]);
     if(strstr(xpath, xkeys->pname[i]))
     {
       printf("----------->%s, %d\n", xkeys->pname[i], strlen(xkeys->pname[i]) );
       sprintf(a+len, "%s{%s}", xkeys->pname[i], xkeys->keys[i]);
       printf("aaa -> %s\n", a);
       len = strlen(a);
     
       xlen-=strlen(xkeys->pname[i]);
     }
     else
     {
       printf("xlen %d\n", xlen);
     }
  }
  if(xlen!=0)
  {
       printf("xlen %d\n", xlen);
       strcpy(a+len, xpath+(total-xlen));
       printf("aaa ---> %s\n", a);
  }
}

#define MAX_XPATH_LENGTH 1024
void wconfd_rmv_keys_from_xpath(const char *xpath, char *rpath)
{
    char *pos1, *pos2;
    int xlen = strlen(xpath);
    int plen;
    int p1;
printf("\n<%s>  :  <%s>\n", xpath, rpath);

    if(rpath == NULL)
    {
        rpath = malloc(MAX_XPATH_LENGTH);
        memset(rpath, 0, MAX_XPATH_LENGTH);
    }
    plen = strlen(rpath);

    if((pos1 = COS_STRCHR(xpath, '{')) != NULL)
    {
        p1 = pos1 - xpath;
        strncpy(rpath + plen, xpath, p1) ;
        rpath[plen + p1] = '\0';
	printf("-----> strlen(rxpath) %d, %s\n", strlen(rpath), rpath);

        pos2 = COS_STRCHR(pos1, '}');
        wconfd_rmv_keys_from_xpath(pos2 + 1, rpath);
    }
    else
    {
        strncpy(rpath + plen, xpath, xlen);
        rpath[plen + xlen] = '\0';
printf("-----> %s\n", rpath); 
    }
}

void resolve_leaf(char *xpath)
{
        char *listpath = strdup(xpath);

        /*remove string after last list
         from /a/b{bk}/c/d{dK}/e/f --> /a/b{bk}/c/d{dK}*/
        char *pos;
        int npos;
        if((pos = strrchr(xpath, '}')) != NULL)
        {
            npos = pos - xpath;
            listpath[npos + 1] = '\0';
        }

     printf("LIST PATH IS ( %s )\n", listpath);
        free(listpath);

}

void split_xpath2array(char *xpath)
{
    char *rpath = strdup(xpath);
    char *p = NULL;
    p = strtok(rpath, "/");
    printf("root is %s\n", p);
    while(p!=NULL){
        p=strtok(NULL,"/");
         if(p)
        printf("--- %s\n", p);
    }
    free(rpath);
}
#endif

#define MAX_LIST_NUMBER  8
#define MAX_KEYS_NUMBER  4
#define MAX_KEYS_LENGTH  128
#define MAX_XPATH_DEPTH  40

typedef struct key_info {
    CHAR buf[MAX_KEYS_LENGTH];
    //enum confd_vtype type;
    //confd_value_t *val;
}KEY_INFO_T;

typedef struct list_keys {
    KEY_INFO_T k[MAX_KEYS_NUMBER];
}LIST_KEYS_T;

typedef struct xpath_array_info {
    WORD32 depth;
    WORD32 keynum;
    WORD32 keymask_0;
    WORD32 keymask_1;
    LIST_KEYS_T listkeys[MAX_LIST_NUMBER];
    WORD32 tagarr[MAX_XPATH_DEPTH];
}XPATH_ARRINFO_T;


VOID wconfd_xpath2array(const CHAR *xpath, XPATH_ARRINFO_T *array_info)
{
    CHAR *prev = NULL;
    CHAR *next = NULL;
    CHAR *pos1 = NULL;
    CHAR *pos2 = NULL;

    CHAR elem[128] = {0};
    SWORD32 depth = 0;

    CHAR keys[MAX_KEYS_LENGTH] = {0};
    SWORD32 key_idx = 0;
    CHAR *keyptr = NULL;
    CHAR *tkeyptr = NULL;
    CHAR *kelem = NULL;
    LIST_KEYS_T *listkeys = NULL;

    SWORD32 xlen = COS_STRLEN(xpath);

    prev = COS_STRCHR(xpath, '/'); //pre
    while (prev - xpath < xlen) {
        next = COS_STRCHR(prev + 1, '/'); //next
        if(!next) { 
            printf("--->last<---\n");
            /* set point to end '\0' */
            next = (char*)xpath + xlen;
        }
        pos1 = COS_STRCHR(prev, '{');
        if (pos1 && pos1 < next) {
            /* process list node which terminated by '{' */
            COS_MEMCPY(elem, prev + 1, pos1 - prev - 1);
            elem[pos1 - prev - 1] = '\0';
            printf("------->copy list %s\n", elem);
            array_info->tagarr[depth++] = 0;//confd_str2hash(elem);

            /* get combined keys */
            pos2 = COS_STRCHR(pos1, '}');
            COS_MEMSET(keys, 0, MAX_KEYS_LENGTH);
            COS_STRNCPY(keys, pos1 + 1, pos2 - (pos1 + 1));

            /* parse all keys */
            key_idx = 0;
            keyptr = (char *)keys;
            listkeys = &array_info->listkeys[array_info->keynum++];
            while ((kelem = strtok_r(keyptr, " ", &tkeyptr)) != NULL) {
                COS_STRNCPY(listkeys->k[key_idx++].buf, kelem, MAX_KEYS_LENGTH);
                printf("\t--> key --> %s\n", kelem);
                keyptr = NULL;
            }

            if (depth < 32) {
                array_info->keymask_0 |= (1 << depth);
            } else {
                array_info->keymask_1 |= (1 << (depth - 32));
            }

            next = pos2 + 1; // "}[/\0]{1}"
        } else {
            /* process other nodes */
            COS_MEMCPY(elem, prev + 1, next - prev - 1);
            elem[next - prev - 1] = '\0';
            printf("------->copy node %s\n", elem);
            array_info->tagarr[depth++] = 0;//confd_str2hash(elem);
        }
        prev = next;
    }

    printf("depth is %d\n", depth);
    array_info->depth = depth;
}

int main()                                 
{                                          
#if 0
    wconfd_xpath_keys_t xkeys;
    memset(&xkeys, 0, sizeof(wconfd_xpath_keys_t));
    
   //char xpath[256]="/a/b{k1}/c/d{k2}/e/f{j}/g{k}";
   //char xpath[256]="/a/b{k1}/c/d{k2}/e/f{j}/g/h/i/j/k";
   char *xpath="/address-pools/address-pool{p333}/address-pool-entries/ipv4-address-block{p2345}/ipv4-prefix-length";
   //char xpath[256]="/a/b/c/d/e/fg/h/i/j/k";
   wconfd_get_keys_from_xpath(xpath, &xkeys);
   //char rpath[256]="/a/b/c/d/e/fg/h/i/j/k";
   char *rpath="/address-pools/address-pool/address-pool-entries/ipv4-address-block";
   resolve_keys(rpath, &xkeys);
  
  int i=0;
 for(;i<xkeys.keys_num;i++)
 {
    printf("@@@@@@@ %s\n", xkeys.pname[i]);
    printf("number of keys is %d, keys %s\n", xkeys.keys_num, xkeys.keys[i]);
  }
#endif

   //char *p1="/a/b{k1 k11}/c/d{k2 k22 /k222}/e/f{j j1 j2 j3}/g/h/i/j{dwjkf/de/de/}";
   //char *p1="/interfaces/interface{10gei-1/1/1}/virtualized";
   char *p1="/abcedfg/abcdef{10gei-1/1/1}/abcde/abcd/abc/ab/a";
  printf("prepare path [ %s ] \n", p1);
  struct xpath_array_info info;
  memset(&info, 0, sizeof(struct xpath_array_info));
  wconfd_xpath2array(p1, &info);

    return 0;                              
}                                          
