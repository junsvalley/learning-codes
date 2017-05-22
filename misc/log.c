#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#define LOG_FILE "/root/confd-test-go/env-confd/confd-types/log.txt"
#define LOG(fmt, ...) do { write_log(__func__, __LINE__, fmt,##__VA_ARGS__); } while(0)

void write_log(const char *func, unsigned int line, const char *fmt, ...)
{
    FILE *fd           = fopen(LOG_FILE, "a+");
    char content[1024] = {0};
    char head[128]     = {0};

    char t_fmt[128]    = {0};
    time_t t_now       = time(0);
    struct tm *tm      = localtime(&t_now);
    strftime(t_fmt, 128, "%Y-%m-%d %H:%M:%S", tm);

    snprintf(head, 128, "%s %-15s line:%-5d[LOG] ", t_fmt, func, line);
    fwrite(head, 1, strlen(head), fd);

    va_list args;
    va_start(args, fmt);

    vsnprintf(content, 1024, fmt, args);

    va_end(args);

    fwrite(content, 1, strlen(content), fd);
    fflush(fd);

    fclose(fd);
}

void log_test()
{
    LOG("test number %d\n", 2017);
    LOG("test string %s\n", "Hello World");
    LOG("\n");
}

int main()
{
    log_test();
    return 0;
}
