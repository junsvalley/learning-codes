#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILE_IPCONF "confd_ip.conf"

int wconfd_ha_clean_ipconf()
{
    FILE *fd = fopen(FILE_IPCONF, "w");
    fclose(fd);
}

int wconfd_ha_write_ipconfd(char *ip, int port)
{
    FILE *fd = fopen(FILE_IPCONF, "w");
    fprintf(fd, "%s:%d", ip, port);
    fclose(fd);
}
void wconfd_ha_confd_server_check ()
{
    FILE *pstr;
    char line_buff[1024] = {0};
    char *cmd = "ps aux | grep  \"confd\\.conf\" | grep -v grep";
    char *need = "lib/confd/erts/bin/confd";
    pstr = popen(cmd, "r");

    if(pstr == NULL)
        return;

    while (fgets(line_buff, sizeof(line_buff), pstr) != NULL)
    {
        if(strstr(line_buff, need))
        {
            //return without do anything
            printf("fffffffffffffind it!!!\n");
            return;
        }
        else
            memset(line_buff, 0, sizeof(line_buff));
    }

    //not found from the results
    //wconfd_ha_stop();
    printf("nooooooooooooooooot exist!!!\n");
    exit(0); //process exit to indicate the confd server down
}

void confdha_ctrl_token_generation(char *token, size_t token_size)
{
    time_t now = time(NULL);
    snprintf(token, 64, "TOKEN%X", now);
}

int main()
{
    char token[64] = {0};
    confdha_ctrl_token_generation(token, 64);
    printf("token is %s\n", token);

    wconfd_ha_clean_ipconf();
    //wconfd_ha_write_ipconfd("127.0.0.1", 5645);
    wconfd_ha_confd_server_check();

    free(1);
}
