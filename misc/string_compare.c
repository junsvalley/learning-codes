#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STATUS_POOL_LOWER_KEY "p1"
#define STATUS_POOL_UPPER_KEY "p1z"

int is_key_name_in_range(const char *keyname)
{
    printf("\n..... %s .....\n", keyname);
    char *c = (char*) keyname;
    char *low = (char*) STATUS_POOL_LOWER_KEY;
    char *up = (char*) STATUS_POOL_UPPER_KEY;
    int c_len = strlen(c);
    int low_len = strlen(low);
    int up_len = strlen(up);
    int i=0;
    int is_all_equal = 1;

    while(c[i] != '\0' && low[i] != '\0') {
        if(c[i] < low[i]) {
            printf("lower than ..........\n");
            return 0;
        } else if(c[i] > low[i]) {
            is_all_equal = 0;
        }
        if(is_all_equal && c_len < low_len) {
            printf("less equal ..........\n");
            return 0;
        }
        i++;
    }

    i=0;
    is_all_equal = 1;
    while(c[i] != '\0' && up[i] != '\0') {
        if(c[i] > up[i]) {
            printf("larger than ..........\n");
            return 0;
        } else if(c[i] < up[i]) {
            is_all_equal = 0;
        }
        if(is_all_equal && c_len > up_len) {
            printf("more equal ..........\n");
            return 0;
        }
        i++;
    }
    printf("PASSED ..........\n");
    return 1;
}

int main()
{
    is_key_name_in_range("p");
    is_key_name_in_range("p1");
    is_key_name_in_range("p10");

    is_key_name_in_range("p1a");
    is_key_name_in_range("p1z");
    is_key_name_in_range("p1z0");
    is_key_name_in_range("p2");
    return 0;
}
