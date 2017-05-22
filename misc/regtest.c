#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

char *ps[]={
"/address-pools/address-pool{a}",
"/address-pools/address-pool{b}/address-pool-entries/ipv4-address-range{d}",
"/address-pools/address-pool{c}/address-pool-entries/ipv6-address-range{e}",
"/address-pool-status/address-pool{f_e}",
"/address-pool-status/address-pool{h-i}/address-pool-entries/ipv4-address-range{j0}",
"/address-pool-status/address-pool{1k}/address-pool-entries/ipv6-address-range{l2}",
"/address-pool-status/address-pool{mm}/address-pool-entries/port-range{nn}",
};

void parse_addr_pool_delete(char *xpath)
{
#if 0
    //printf("Delete: %s\n", xpath);
    int status;
    int cflags=0;//REG_EXTENDED;
    regex_t reg;
    regmatch_t pm[1];
    const size_t nmatch = 1;
    char *pattern = "address-pool\\{[\\w]+\\}";
    printf("%s --*--", pattern);
    regcomp(&reg, pattern, cflags);
    status = regexec(&reg, xpath, 0, NULL, 0);
    //status = regexec(&reg, xpath, nmatch, pm, 0);
      printf("MATCH STATUS--------->%d\n", status);
    regfree(&reg);
#endif
    char *pos1 = strchr(xpath, '{');
 //  printf("'{' at %d, %s\n", pos1-xpath, pos1);
    char *pos2 =   strchr(pos1, '}');
  // printf("'}' at %d, %s\n", pos2-pos1, pos2);
    char key[128]={0};   
    strncpy(key, pos1+1, pos2-(pos1+1)); 
   printf("key is : %s \n", key); 

    char *pos3 = strchr(pos2, '{');
  if(pos3){
 //  printf("'{' at %d, %s\n", pos3-xpath, pos3);
    char *pos4 =   strchr(pos3, '}');
//   printf("'}' at %d, %s\n", pos4-pos3, pos4);
    char ikey[128]={0};   
    strncpy(ikey, pos3+1, pos4-(pos3+1)); 
   printf("-->key is : %s \n", ikey); 
  }
}

int main()
{
  int i=0;
  for(;i<7;i++)
  {
    parse_addr_pool_delete(ps[i]);
    //printf("%s\n", ps[i]);
  }
  return 0;
}


