#ifndef __HIGH_CONCURRENCY_H__
#define __HIGH_CONCURRENCY_H__
#include <time.h>

#define SERVER_PORT 2016
#define SERVER_ADDR "127.0.0.1"//"10.0.2.15"
#define SERVER_CAPACITY 1000//100000
#define SERVER_MAX_HANDLER 10

#define SERVER_MAX_EPOLLEVENTS 20
#define SERVER_EPOLL_CAPACITY 100//10000
#define SERVER_EPOLL_WAIT -1
#define SERVER_EPOLL_NOWAIT 0
#define SERVER_EPOLL_WAITTIMEOUT 500 //500ms

#define RCV_BUFSIZ 1024
#define SND_BUFSIZ 1024

#define TRUE 1
#define FALSE 0

#define GET_TIME_NOW_MS()({\
    struct timeval tnowv;\
    gettimeofday(&tnowv, NULL);\
    (int64_t)tnowv.tv_sec * 1000 + tnowv.tv_usec / 1000;\
    })

#define GET_TIME_FORMAT_STR()({\
    char tformatstr[128]={0};\
    time_t tformatt =time(0);\
    struct tm *tformatptr = localtime(&tformatt);\
    strftime(tformatstr, 128, "%Y-%m-%d %H:%M:%S", tformatptr);\
    tformatstr;\
    })

#define TIME_NOW_MS     GET_TIME_NOW_MS()
#define TIME_FORMAT_STR GET_TIME_FORMAT_STR()

#define HC_PRINT(format, ...){\
  fprintf(stderr, "%s %-15s line:%-5d[DEBUG] "format, TIME_FORMAT_STR, __func__, __LINE__, ##__VA_ARGS__);\
}

#define CHK_OK(E) {if((E) < 0)HC_PRINT("%s\n", strerror(errno));}
#define CHK_PTR(E) assert((E) != NULL)

#endif

