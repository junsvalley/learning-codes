/*****************************************************************************/
/** 
 * * \file       cos_types.h
 * * \author     felix
 * * \date       2015/01/27
 * * \version    FlexBNG V1
 * * \brief      »ù±¾Êý¾ÝÀàÐÍ¶¨Òå
 * * \note       Copyright (c) 2000-2020  ÈüÌØË¹ÐÅÏ¢¿Æ¼¼¹É·ÝÓÐÏÞ¹«Ë¾
 * * \remarks    ÐÞ¸ÄÈÕÖ¾
 * ******************************************************************************/
#ifndef _COS_TYPES_H_
#define _COS_TYPES_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/types.h>
#include <sys/eventfd.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#define CODE_PART(x)                      1         /* ´úÂëÔÄ¶Áºê */
//#include "cos_odt.h"                                /* ¸ÃÎÄ¼þÖÐÊ¹ÓÃÁËCODE_PARTºê,ËùÒÔ±ØÐëÔÚ¸Ãºê¶¨Òåºóinclude */

#if CODE_PART("Êý¾ÝÀàÐÍ")
/* »ù´¡Êý¾ÝÀàÐÍ */
typedef unsigned char                     BYTE;
typedef char                              SBYTE;
typedef char                              CHAR;
typedef unsigned char                     BOOL;      /* TRUE(1)/FALSE(0), ½á¹¹ÌåÖÐÊ¹ÓÃ×¢Òâ²¹Æë */
typedef void                              VOID;
typedef unsigned short                    WORD16;
typedef signed short                      SWORD16;
typedef unsigned int                      WORD32;
typedef signed int                        SWORD32;
typedef int                               INT;       /* ½¨ÒéÊ¹ÓÃSWORD32 */
typedef unsigned long                     ULONG;
typedef long                              LONG;
typedef unsigned long long                WORD64;
typedef long long                         SWORD64;
typedef float                             FLOAT;
typedef signed   long int                 SWORDPTR;  /* ÓëÖ¸Õë´óÐ¡ÏàÍ¬µÄWORDÀàÐÍ, 32Î»»òÕß64Î» */
typedef unsigned long int                 WORDPTR;   /* ÓëÖ¸Õë´óÐ¡ÏàÍ¬µÄWORDÀàÐÍ, 32Î»»òÕß64Î» */

/* À©Õ¹Êý¾ÝÀàÐÍ */
typedef size_t                            SIZE_T;    /* unsigned long, ³£ÓÃÓÚ±íÊ¾buffer·Ç¸º³¤¶È */
typedef ssize_t                           SSIZE_T;   /* long int, ³£ÓÃÓÚread¡¢writeµÄ·µ»ØÖµ */
typedef pid_t                             PID_T;

typedef struct epoll_event                EPOLL_EVENT;

typedef sem_t                             SEM_T;                  /* ÐÅºÅÁ¿ÀàÐÍ */
typedef pthread_mutex_t                   PTHREAD_MUTEX_T;        /* »¥³âËøÀàÐÍ */
typedef pthread_mutexattr_t               PTHREAD_MUTEXATTR_T;    /* »¥³âËøÊôÐÔ */
typedef pthread_t                         PTHREAD_T;              /* Ïß³ÌIDÀàÐÍ */

typedef time_t                            TIME_T;   /* broken-down time, ·Ö½âÊ±¼ä 
                                                       ÄêÔÂÈÕÊ±·ÖÃë·Ö¿ªÏÔÊ¾µÄÊ±¼ä¸ñÊ½ */
typedef struct tm                         TM;       /* calendar time, ÈÕÀúÊ±¼ä, long, 
                                                       ´Ó1970Äê1ÔÂ1ÈÕ0Ê±0·Ö0ÃëÖÁ´ËËù¾­¹ýµÄÃëÊý */
typedef struct timeval                    TIMEVAL;  /* s & ms, clock_gettime() */
typedef struct timespec                   TIMESPEC; /* s & ns, gettimeofday() */

/* BOOL */
#undef  TRUE
#define TRUE                              1
#undef  FALSE
#define FALSE                             0
#endif

#if CODE_PART("»ù´¡²Ù×÷ºê")
#define COS_SIZEOF(x)                     sizeof(x)
#define COS_ABS(x)                        (((x) > 0) ? (x) : -(x))
#define COS_MAX(A, B)                     (((A) > (B)) ? (A) : (B))
#define COS_MIN(A, B)                     (((A) < (B)) ? (A) : (B))

#if CODE_PART("bit²Ù×÷")
#define COS_BYTE_BITS                     8                             /* BYTEµÄbitÊý */
#define COS_BYTE_MAX                      0xff                          /* BYTE×î´óÖµ */

#define COS_BIT_SET(F, B)                 ((F) |= (B))
#define COS_BIT_RESET(F, B)               ((F) &= ~(B))
#define COS_BIT_TEST(F, B)                ((F) & (B))
#define COS_BIT_MATCH(F, B)               (((F) & (B)) == (B))

#define COS_BIT_AND(A, B)                 ((A) & (B))
#define COS_BIT_OR(A, B)                  ((A) | (B))
#define COS_BIT_XOR(A, B)                 ((A) ^ (B))
#define COS_BIT_ANTI(A)                   (~(A))

#define COS_BUILD_64(H, L)                (((WORD64)(H) << 32) | (L))
#define COS_PARSE_64(C, A, B) \
do{ \
    *A = (C) >> 32; \
    *B = ((C) << 32) >> 32; \
}while(0)
#endif

#if CODE_PART("Ëæ»úÊý")
#define COS_RAND_NOZERO()                 ((((WORD32)RAND()) % RAND_MAX) + 1)
#define COS_RAND()                        rand()
#define COS_SRAND(seed)                   srand(seed)
#endif

#if CODE_PART("½á¹¹ÌåÆ«ÒÆ")
#define COS_VAROFFSET(type, member)               ((ULONG)(&((type *)0)->member))
#define COS_GET_STRUCT_PTR(node, type, member)    ((type *)((BYTE*)(node) - COS_VAROFFSET(type,member)))
#endif

#if CODE_PART("×Ö·û²Ù×÷")
#define COS_IS_SPACE(c)                   ((c) == ' ' || ((c) >= '\t' && (c) <= '\r'))   /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇ¿Õ¸ñ */
#define COS_IS_SLASH(c)                   ((c) == '/')                                   /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇÐ±¸Ü */
#define COS_IS_POINT(c)                   ((c) == '.')                                   /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇµã */
#define COS_IS_ASCII(c)                   (((c) & ~0x7f) == 0)                           /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇASCIIÂë */
#define COS_IS_UPPER(c)                   ((c) >= 'A' && (c) <= 'Z')                     /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇ´óÐ´×ÖÄ¸ */
#define COS_IS_LOWER(c)                   ((c) >= 'a' && (c) <= 'z')                     /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇÐ¡Ð´×ÖÄ¸ */
#define COS_IS_ALPHA(c)                   (COS_IS_UPPER(c) || COS_IS_LOWER(c))           /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇ×ÖÄ¸ */
#define COS_IS_DIGIT(c)                   ((c) >= '0' && (c) <= '9')                     /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇÊý×Ö */
#define COS_IS_ALNUM(c)                   (COS_IS_ALPHA(c) || COS_IS_DIGIT(c))
#define COS_IS_XDIGIT(c)                  (COS_IS_DIGIT(c) \
                                           || ((c) >= 'A' && (c) <= 'F') \
                                           || ((c) >= 'a' && (c) <= 'f'))                /* ÅÐ¶Ï×Ö·ûÊÇ·ñÊÇ16½øÖÆÊý×Ö */                                  
#define COS_IS_PRINT(c)                   ((c) >= ' ' && (c) <= '~')                     /* ÅÐ¶Ï×Ö·ûÊÇ·ñ¿ÉÒÔ´òÓ¡³öÀ´ */
#define COS_TO_UPPER(c)                   ((c) - 0x20 * (((c) >= 'a') && ((c) <= 'z')))  /* ½«×Ö·û×ª»»Îª´óÐ´ */
#define COS_TO_LOWER(c)                   ((c) + 0x20 * (((c) >= 'A') && ((c) <= 'Z')))  /* ½«×Ö·û×ª»»ÎªÐ¡Ð´ */
#endif

#if CODE_PART("×Ö½ÚÐò")
/* TRUE: big endian; FALSE: little endian */
#define COS_BIG_ENDIAN                    cos_big_endian()

/* ×Ö½ÚÐò·­×ª */
#define COS_INVERT_16(x)                  ((((x) & 0xff00) >> 8) |    \
                                           (((x) & 0x00ff) << 8))
#define COS_INVERT_32(x)                  ((((x) & 0xff000000) >> 24) |    \
                                           (((x) & 0x00ff0000) >> 8) |    \
                                           (((x) & 0x0000ff00) << 8) |    \
                                           (((x) & 0x000000ff) << 24))
#define COS_INVERT_64(x)                  ((((x) & 0xff00000000000000ull) >> 56) |    \
                                           (((x) & 0x00ff000000000000ull) >> 40) |    \
                                           (((x) & 0x0000ff0000000000ull) >> 24) |    \
                                           (((x) & 0x000000ff00000000ull) >> 8) |    \
                                           (((x) & 0x00000000ff000000ull) << 8) |    \
                                           (((x) & 0x0000000000ff0000ull) << 24) |    \
                                           (((x) & 0x000000000000ff00ull) << 40) |    \
                                           (((x) & 0x00000000000000ffull) << 56))

/* Ö÷»úÐòÓëÍøÂçÐò»¥×ª */
#define COS_HTON_16(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_16(x))
#define COS_NTOH_16(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_16(x))
#define COS_HTON_32(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_32(x))
#define COS_NTOH_32(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_32(x))
#define COS_HTON_64(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_64(x))
#define COS_NTOH_64(x)                    (COS_BIG_ENDIAN ? (x) : COS_INVERT_64(x))
#endif
#endif

#if CODE_PART("×Ö·û´®²Ù×÷")
#define COS_STRLEN(dst)                   strlen(dst)                 
#define COS_STRCPY(dst, src)              strcpy(dst, src)             
#define COS_STRNCPY(dst, src, n)          strncpy(dst, src, n)
#define COS_STRCAT(dst, src)              strcat(dst, src)              
#define COS_STRNCAT(dst, src, n)          strncat(dst, src, n)
#define COS_STRCMP(dst, src)              strcmp(dst, src)   
#define COS_STRNCMP(dst, src, n)          strncmp(dst, src, n)
#define COS_STRCASECMP(dst, src)          strcasecmp(dst, src)
#define COS_STRNCASECMP(dst, src, n)      strncasecmp(dst, src, n)
#define COS_STRCHR(str, chr)              strchr(str, chr)
#define COS_STRRCHR(str, chr)             strrchr(str, chr)
#define COS_STRSTR(str1, str2)            strstr(str1, str2)          
#define COS_STRTOK(str1, str2)            strtok(str1, str2)           
#define COS_ATOI(str)                     atoi(str)                     
#define COS_STRTOUL(str, endchar, base)   strtoul(str, endchar, base)   
#define COS_STRDUP(odt, str)              strdup(str)
#endif

#if CODE_PART("ÄÚ´æ²Ù×÷")
#define COS_MALLOC(odt, app_len)          malloc(app_len)//memmgr_create(odt, app_len)
#define COS_CALLOC(odt, cnt, app_len)     calloc(app_len, cnt)//memmgr_calloc(odt, cnt, app_len)
#define COS_REALLOC(app_mem, app_len)     realloc(app_mem, app_len)//memmgr_realloc(app_mem, app_len)
#define COS_FREE(app_mem)                 free(app_mem)//memmgr_delete(app_mem)
#define COS_MEMSET(dst, var, n)           memset(dst, var, n)
#define COS_MEMCMP(dst, src, n)           memcmp(dst, src, n)
#define COS_MEMCPY(dst, src, n)           memcpy(dst, src, n)           /* dst,srcÄÚ´æÓÐÖØµþÊ±ÐèÒªÊ¹ÓÃCOS_MEMMOVE */
#define COS_MEMCHR(dst, src, n)           memchr(dst,src,n)
#define COS_MEMMOVE(dst, src, n)          memmove(dst,src,n)            /* dst,srcÄÚ´æÓÐÖØµþÊ±Ê¹ÓÃ */
#define COS_MEMCPY64(key, arg1, arg2) \
do{ \
    if(COS_SIZEOF(key) >= COS_SIZEOF(arg1) + COS_SIZEOF(arg2)) \
    { \
        COS_MEMCPY(&key, &arg1, COS_SIZEOF(arg1)); \
        COS_MEMCPY((CHAR*)&key + COS_SIZEOF(arg1), &arg2, COS_SIZEOF(arg2)); \
    } \
}while(0)



#define COS_MEM_SIGN_DEFINE               WORDPTR __mem_sign

#define COS_MEM_SIGN_SET(mem, sign)       ((mem)->__mem_sign = (WORDPTR)(mem) + (BYTE)(sign))

#define COS_MEM_SIGN_CHECK(mem, sign)     (((mem)->__mem_sign == (WORDPTR)(mem) + (BYTE)(sign)) ? TRUE : (COS_ASSERT(0), FALSE))
#endif

#if CODE_PART("print²Ù×÷")
#define COS_PRINTF                        printf    /* Ô­ÔòÒªÇóÕýÊ½³ÌÐòÖÐ²»ÔÊÐíÊ¹ÓÃ */
#define COS_SPRINTF                       sprintf   /* ¸ñÊ½»¯×Ö·û´®¸´ÖÆ */
#define COS_SNPRINTF                      snprintf  /* ×¢Òâ: ·µ»ØÖµÎªÓûÌî³äµÄ×Ö·û³¤¶È(¿ÉÄÜ´óÓÚbuff³¤¶È) */
#define COS_VSNPRINTF                     vsnprintf /* ¸ñÊ½»¯Êä³ö¿É±ä²ÎÊýÁÐ±íva_list */
#define COS_PUTCHAR                       putchar   /* ½«Ö¸¶¨µÄ×Ö·ûÐ´µ½±ê×¼Êä³öÉè±¸ */
#define COS_SSCANF                        sscanf    /* ¸ñÊ½»¯×Ö·û´®ÊäÈë */
#endif

#if CODE_PART("ÎÄ¼þ²Ù×÷")

#define COS_FD_INVALID                    -1
#define COS_FD_STDIN                      STDIN_FILENO
#define COS_FD_STDOUT                     STDOUT_FILENO
#define COS_FD_STDERR                     STDERR_FILENO


#define COS_SEEK_SET                      SEEK_SET
#define COS_SEEK_CUR                      SEEK_CUR
#define COS_SEEK_END                      SEEK_END

#define COS_REMOVE(path)                  remove(path)          /* ¿ÉÉ¾³ýÎÄ¼þ»òÄ¿Â¼ */
#define COS_RENAME(old, new)              rename(old, new)


#define COS_OPENDIR(path)                 opendir(path)
#define COS_MKDIR(path, mode)             mkdir(path, mode)


#define COS_O_RDONLY                      O_RDONLY
#define COS_O_WRONLY                      O_WRONLY
#define COS_O_RDWR                        O_RDWR
#define COS_O_APPEND                      O_APPEND
#define COS_O_CREAT                       O_CREAT
#define COS_O_EXCL                        O_EXCL
#define COS_O_TRUNC                       O_TRUNC
#define COS_O_NOCTTY                      O_NOCTTY
#define COS_O_NONBLOCK                    O_NONBLOCK

#define COS_F_DUPFD                       F_DUPFD
#define COS_F_GETFD                       F_GETFD
#define COS_F_SETFD                       F_SETFD
#define COS_F_GETFL                       F_GETFL
#define COS_F_SETFL                       F_SETFL

/* ÓÃÓÚ×éºÏCOS_ACCESSÖÐ²ÎÊýmodeµÄÖµ */
#define COS_R_OK                          R_OK      /* ÎÄ¼þ¾ßÓÐ¶ÁÈ¡È¨ÏÞ */
#define COS_W_OK                          W_OK      /* ÎÄ¼þ¾ßÓÐÐ´ÈëÈ¨ÏÞ */
#define COS_X_OK                          X_OK      /* ÎÄ¼þ¾ßÓÐÖ´ÐÐÈ¨ÏÞ */
#define COS_F_OK                          F_OK      /* ÎÄ¼þ´æÔÚ */

#define COS_OPEN(path, flags, ...)        open(path, flags, __VA_ARGS__)
#define COS_CLOSE(fd)                     close(fd)
#define COS_ACCESS(path, mode)            access(path, mode)    /* ºË²émode£¬¼ì²â¾ù³É¹¦·µ»Ø0£¬ÈÎÒ»Ê§°Ü·µ»Ø-1 */
#define COS_STAT(path, buff)              stat(path, buff)      /* »ñÈ¡ÎÄ¼þÊôÐÔ */
#define COS_UNLINK(path)                  unlink(path)          /* É¾³ýÎÄ¼þ²¢¼õÉÙËüµÄÁ´½ÓÊý */
#define COS_SEND(fd, buff, size, flags)   send(fd, buff, size, flags)
#define COS_SENDTO(fd, buff, size, flags, to, tolen)          sendto(fd, buff, size, flags, to, tolen)
#define COS_RECV(fd, buff, size, flags)   recv(fd, buff, size, flags)
#define COS_RECVFROM(fd, buff, size, flags, from, fromlen)    recvfrom(fd, buff, size, flags, from, fromlen)
#define COS_READ(fd, buff, size)          read(fd, buff, size)
#define COS_WRITE(fd, buff, size)         write(fd, buff, size)
#define COS_FCNTL(fd, cmd, ...)           fcntl(fd, cmd, __VA_ARGS__)
#define COS_LSEEK(fd, offset, pos)        lseek(fd, offset, pos)
#define COS_DUP(oldfd)                    dup(oldfd)            /* ¸´ÖÆÎÄ¼þÃèÊö·û */
#define COS_DUP2(oldfd, targetfd)         dup2(oldfd, targetfd)
#define COS_ISATTY(fd)                    isatty(fd)            /* ÅÐ¶ÏÎÄ¼þÃèÊö·ûÊÇ·ñÎªÖÕ¶Ë»ú */
#define COS_TTYNAME(fd)                   ttyname(fd)           /* ·µ»ØÒ»ÖÕ¶Ë»úÃû³Æ */

#define COS_FOPEN(path, mode)             fopen(path, mode)
#define COS_FCLOSE(fp)                    fclose(fp)
#define COS_FGETS(str, num, fp)           fgets(str, num, fp)
#define COS_FPUTS(str, fp)                fputs(str, fp)
#define COS_FSEEK(fp, offset, pos)        fseek(fp, offset, pos)
#define COS_FTELL(fp)                     ftell(fp)
#define COS_FFLUSH(fp)                    fflush(fp)
#endif

#if CODE_PART("eventfd")
#define COS_EFD_NONBLOCK                  EFD_NONBLOCK
#define COS_EFD_CLOEXEC                   EFD_CLOEXEC 
#define COS_EVENTFD(initval, flags)       eventfd(initval, flags)
#endif

#if CODE_PART("²Ù×÷ÏµÍ³·þÎñunistd.h")
#define COS_GETOPT(argc, argv, optstr)    getopt(argc, argv, optstr)    /* ·ÖÎöÃüÁîÐÐ²ÎÊý */
#define COS_GETPID                        getpid()                      /* È¡µÃ½ø³ÌÊ¶±ðÂë */
#define COS_READLINK(path, buff, size)    readlink(path, buff, size)    /* È¡µÃ·ûºÅÁ¬½ÓËùÖ¸µÄÎÄ¼þ */
#define COS_GETCWD(buff, size)            getcwd(buff, size)            /* È¡µÃµ±Ç°µÄ¹¤×÷Ä¿Â¼ */
#define COS_SLEEP(sec)                    sleep(sec)
#define COS_USLEEP(usec)                  usleep(usec)
#endif

#if CODE_PART("µ÷ÓÃ¶ÑÕ»execinfo.h")
/* µ±Ç°Ïß³ÌµÄº¯Êýµ÷ÓÃ¶ÑÕ»£¬Ã¿Ìõ¼ÇÂ¼µÄÖ¸Õë±£´æÔÚbufferÖÐ£¬×î´óÓÐsizeÌõ¼ÇÂ¼ */
#define COS_BACKTRACE(buff, size)                   backtrace(buff, size)
/* »ñÈ¡µ÷ÓÃ¶ÑÕ»ÐÅÏ¢£¬²¢·µ»Ø×Ö·û´®Êý×é£¬ÄÚº¬malloc²Ù×÷£¬»ñÈ¡ÐÅÏ¢Íê³ÉºóÐèfree */
#define COS_BACKTRACE_SYMBOLS(buff, size)           backtrace_symbols(buff, size)
/* »ñÈ¡µ÷ÓÃ¶ÑÕ»ÐÅÏ¢£¬½«½á¹ûÐ´ÈëÎÄ¼þÃèÊö·ûÎªfdµÄÎÄ¼þÖÐ,Ã¿¸öº¯Êý¶ÔÓ¦Ò»ÐÐ */
#define COS_BACKTRACE_SYMBOLS_FD(buff, size, fd)    backtrace_symbols_fd(buff, size, fd)
#endif

#if CODE_PART("ÐÅºÅsignal.h")
#define COS_SIG_ERR                       SIG_ERR
#define COS_SIG_DFL                       SIG_DFL
#define COS_SIG_IGN                       SIG_IGN

/* ÔÝ¶¨ÒåÈçÏÂÐÅºÅ,ÈôÐèÆäËüÐÅºÅÔÙ¶¨Òå,#kill -l¿É²é¿´ */
#define COS_SIGINT                        SIGINT    /* 2-¼üÅÌÖÐ¶Ï(Èçbreak¼ü¡¢ctrl+c±»°´ÏÂ) */
#define COS_SIGQUIT                       SIGQUIT   /* 3-¼üÅÌÍË³ö¼ü±»°´ÏÂ */
#define COS_SIGILL                        SIGILL    /* 4-·Ç·¨Ö¸Áî */
#define COS_SIGTRAP                       SIGTRAP   /* 5-ÓÉ¶ÏµãÖ¸Áî»òÆäËütrapÖ¸Áî²úÉú */
#define COS_SIGABRT                       SIGABRT   /* 6-µ÷ÓÃabort() */
#define COS_SIGBUS                        SIGBUS    /* 7-·Ç·¨µØÖ·,°üÀ¨ÄÚ´æµØÖ·¶ÔÆë(alignment)³ö´í*/
#define COS_SIGFPE                        SIGFPE    /* 8-¸¡µãÒì³£ */
#define COS_SIGSEGV                       SIGSEGV   /* 11-ÎÞÐ§µÄÄÚ´æÒýÓÃ */
#define COS_SIGPIPE                       SIGPIPE   /* 13-¹ÜµÀÆÆÁÑ(Ä¬ÈÏÐÐÎª:½ø³ÌÍË³ö) */
#define COS_SIGTERM                       SIGTERM   /* 15-³ÌÐò½áÊø(terminate)ÐÅºÅ */
#define COS_SIGCHLD                       SIGCHLD   /* 17-×Ó½ø³Ì½áÊøÊ±,¸¸½ø³Ì»áÊÕµ½Õâ¸öÐÅºÅ */
#define COS_SIGXCPU                       SIGXCPU   /* 24-³¬¹ýCPUÊ±¼ä×ÊÔ´ÏÞÖÆ */
#define COS_SIGXFSZ                       SIGXFSZ   /* 25-³¬¹ýÎÄ¼þ´óÐ¡×ÊÔ´ÏÞÖÆ */
#define COS_SIGSYS                        SIGSYS    /* 31-·Ç·¨µÄÏµÍ³µ÷ÓÃ */

#define COS_SIGNAL(sig, func)             signal(sig, func)
#define COS_KILL(pid, sig)                kill(pid, sig)
#endif

#if CODE_PART("epoll")
#define COS_EPOLL_CTL_ADD                           EPOLL_CTL_ADD       /* ×¢²áÐÂµÄfdµ½epfdÖÐ */
#define COS_EPOLL_CTL_MOD                           EPOLL_CTL_MOD       /* ÐÞ¸ÄÒÑ¾­×¢²áµÄfdµÄ¼àÌýÊÂ¼þ */
#define COS_EPOLL_CTL_DEL                           EPOLL_CTL_DEL       /* ´ÓepfdÖÐÉ¾³ýÒ»¸öfd */

#define COS_EPOLL_CREATE(size)                      epoll_create(size)
#define COS_EPOLL_CTL(epfd, op, fd, ev)             epoll_ctl(epfd, op, fd, ev)
#define COS_EPOLL_WAIT(epfd, ev, maxev, timeout)    epoll_wait(epfd, ev, maxev, timeout)
#endif

#if CODE_PART("ÐÅºÅÁ¿")
#define COS_SEM_INIT(sem, pshared, value)           sem_init(sem, pshared, value)
#define COS_SEM_WAIT(sem)                           sem_wait(sem)
#define COS_SEM_POST(sem)                           sem_post(sem)
#endif

#if CODE_PART("»¥³âËø")
#define COS_PTHREAD_MUTEX_INITIALIZER               PTHREAD_MUTEX_INITIALIZER       /* ¾²Ì¬³õÊ¼»¯ */
#define COS_PTHREAD_MUTEX_INIT(mutex, attr)         pthread_mutex_init(mutex, attr) /* ¶¯Ì¬³õÊ¼»¯ */
#define COS_PTHREAD_MUTEX_DESTROY(mutex)            pthread_mutex_destroy(mutex)
#define COS_PTHREAD_MUTEX_LOCK(mutex)               pthread_mutex_lock(mutex)
#define COS_PTHREAD_MUTEX_UNLOCK(mutex)             pthread_mutex_unlock(mutex)
#define COS_PTHREAD_MUTEXATTR_INIT(attr)            pthread_mutexattr_init(attr)

/* ÀàÐÍ»¥³âÁ¿ÊôÐÔ */
#define COS_PTHREAD_MUTEX_DEFAULT                   PTHREAD_MUTEX_DEFAULT           /* 0 */
#define COS_PTHREAD_MUTEX_NORMAL                    PTHREAD_MUTEX_NORMAL            /* 0 */
#define COS_PTHREAD_MUTEX_RECURSIVE                 PTHREAD_MUTEX_RECURSIVE         /* 1 */
#define COS_PTHREAD_MUTEX_ERRORCHECK                PTHREAD_MUTEX_ERRORCHECK        /* 2 */
#define COS_PTHREAD_MUTEXATTR_GETTYPE(attr, type)   pthread_mutexattr_gettype(attr, type)
#define COS_PTHREAD_MUTEXATTR_SETTYPE(attr, type)   pthread_mutexattr_settype(attr, type)
#endif

#if CODE_PART("Ïß³Ì")
#define COS_PTHREAD_CREATE(thd, attr, start, arg)   pthread_create(thd, attr, start, arg)
#define COS_PTHREAD_DETACH(tid)                     pthread_detach(tid) /* ÉèÖÃÏß³Ì×´Ì¬Îªdetached,µ±Ïß³ÌÍË³öÊ±ÊÍ·Å×ÊÔ´ */
#define COS_PTHREAD_SELF                            pthread_self()      /* ±¾Ïß³ÌµØÖ·(%p) */
#define COS_PTHREAD_ID                              cos_tid_get()       /* ±¾Ïß³Ìid(LWP,WORD32) */
#endif

#if CODE_PART("time")
#define COS_GETTIMEOFDAY(tv, tz)          gettimeofday(tv, tz)
#define COS_LOCALTIME_R(time, tm)         localtime_r(time, tm)         /* Ïß³Ì°²È«µÄ */
#define COS_CLOCK_GETTIME(clock, tp)      clock_gettime(clock, tp)
#endif

#if CODE_PART("errno")
#define COS_ERRNO                         errno
#define COS_STRERROR                      strerror(errno)
#endif

#if CODE_PART("¶ÏÑÔ")
/* ½Ó¹Üassert */
//#define COS_ASSERT(x)                     ((x) ? (VOID)0 : cos_proc_assert_entry(__FILE__,    
//                                           __FUNCTION__, __LINE__, #x, COS_SIGASSERT))
#define COS_ASSERT(x)  assert(x)
#endif

/********************************************************************************
 *  *                            ÒµÎñ<²»ÔÊÐí>Ö±½ÓÊ¹ÓÃ                              *
 *   ********************************************************************************/
#define COS_DEVELOP      1    /* develop·ÖÖ§¿ª·Å¹¦ÄÜ */
#define COS_SIGASSERT    -1 
#define COS_ABORT()      abort()
BOOL cos_big_endian();
WORD32 cos_tid_get();
VOID *memmgr_create(WORD32 odt, WORD32 app_len);
VOID *memmgr_calloc(WORD32 odt, WORD32 cnt, WORD32 app_len);
VOID *memmgr_realloc(VOID *app_mem, WORD32 app_len);
CHAR *memmgr_strdup(WORD32 odt, const CHAR *str);
VOID memmgr_delete(VOID *app_mem);
VOID cos_proc_assert_entry(const CHAR *file, const CHAR *func, WORD32 line, 
                           const CHAR *exp_str, SWORD32 sign);

#ifdef __cplusplus
}
#endif


/*
 * This file defines five types of data structures: singly-linked lists,
 * singly-linked tail queues, lists, tail queues, and circular queues.
 *
 * A singly-linked list is headed by a single forward pointer. The elements
 * are singly linked for minimum space and pointer manipulation overhead at
 * the expense of O(n) removal for arbitrary elements. New elements can be
 * added to the list after an existing element or at the head of the list.
 * Elements being removed from the head of the list should use the explicit
 * macro for this purpose for optimum efficiency. A singly-linked list may
 * only be traversed in the forward direction.  Singly-linked lists are ideal
 * for applications with large datasets and few or no removals or for
 * implementing a LIFO queue.
 *
 * A singly-linked tail queue is headed by a pair of pointers, one to the
 * head of the list and the other to the tail of the list. The elements are
 * singly linked for minimum space and pointer manipulation overhead at the
 * expense of O(n) removal for arbitrary elements. New elements can be added
 * to the list after an existing element, at the head of the list, or at the
 * end of the list. Elements being removed from the head of the tail queue
 * should use the explicit macro for this purpose for optimum efficiency.
 * A singly-linked tail queue may only be traversed in the forward direction.
 * Singly-linked tail queues are ideal for applications with large datasets
 * and few or no removals or for implementing a FIFO queue.
 *
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before
 * or after an existing element or at the head of the list. A list
 * may only be traversed in the forward direction.
 *
 * A tail queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may be traversed in either direction.
 *
 * A circle queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or after
 * an existing element, at the head of the list, or at the end of the list.
 * A circle queue may be traversed in either direction, but has a more
 * complex end of list detection.
 *
 * For details on the use of these macros, see the queue(3) manual page.
 *
 *
 *                    SLIST     LIST    STAILQ   TAILQ   CIRCLEQ
 * _HEAD                +        +        +        +        +
 * _HEAD_INITIALIZER    +        +        +        +        +
 * _ENTRY               +        +        +        +        +
 * _INIT                +        +        +        +        +
 * _EMPTY               +        +        +        +        +
 * _FIRST               +        +        +        +        +
 * _NEXT                +        +        +        +        +
 * _PREV                -        -        -        +        +
 * _LAST                -        -        +        +        +
 * _FOREACH             +        +        +        +        +
 * _FOREACH_REVERSE     -        -        -        +        +
 * _INSERT_HEAD         +        +        +        +        +
 * _INSERT_BEFORE       -        +        -        +        +
 * _INSERT_AFTER        +        +        +        +        +
 * _INSERT_TAIL         -        -        +        +        +
 * _REMOVE_HEAD         +        -        +        -        -
 * _REMOVE              +        +        +        +        +
 *
 */

#if CODE_PART("Singly-linked List")
/*
 * Singly-linked List declarations.
 */
#define COS_SLIST_HEAD(name, type)                        \
struct name {                                \
    struct type *slh_first;    /* first element */            \
}

#define COS_SLIST_HEAD_INITIALIZER(head)                    \
    { NULL }
 
#define COS_SLIST_ENTRY(type)                        \
struct {                                \
    struct type *sle_next;    /* next element */            \
}
 
/*
 * Singly-linked List functions.
 */
#define COS_SLIST_EMPTY(head)    ((head)->slh_first == NULL)

#define COS_SLIST_ENTRY_INIT(elm, field) do {    \
    (elm)->field.sle_next = NULL;    \
} while (0)

#define COS_SLIST_FIRST(head)    ((head)->slh_first)

#define COS_SLIST_FOREACH(var, head, field)                    \
    for ((var) = COS_SLIST_FIRST((head));                \
        (var);                            \
        (var) = COS_SLIST_NEXT((var), field))

#define COS_SLIST_INIT(head) do {                        \
    COS_SLIST_FIRST((head)) = NULL;                    \
} while (0)

#define COS_SLIST_INSERT_AFTER(slistelm, elm, field) do {            \
    COS_SLIST_NEXT((elm), field) = COS_SLIST_NEXT((slistelm), field);    \
    COS_SLIST_NEXT((slistelm), field) = (elm);                \
} while (0)

#define COS_SLIST_INSERT_HEAD(head, elm, field) do {            \
    COS_SLIST_NEXT((elm), field) = COS_SLIST_FIRST((head));            \
    COS_SLIST_FIRST((head)) = (elm);                    \
} while (0)

#define COS_SLIST_NEXT(elm, field)    ((elm)->field.sle_next)

#define COS_SLIST_REMOVE(head, elm, type, field) do {            \
    if (COS_SLIST_FIRST((head)) == (elm))    \
    {    \
        COS_SLIST_REMOVE_HEAD((head), field);            \
    }    \
    else    \
    {    \
        struct type *curelm = COS_SLIST_FIRST((head));        \
        while (COS_SLIST_NEXT(curelm, field) != (elm))        \
        {    \
            curelm = COS_SLIST_NEXT(curelm, field);        \
        }    \
        COS_SLIST_NEXT(curelm, field) =                \
            COS_SLIST_NEXT(COS_SLIST_NEXT(curelm, field), field);    \
    }    \
    COS_SLIST_ENTRY_INIT((elm), field);    /* ɾ³ýõ¯ */    \
} while (0)

/* ɾ³ýڵã¾³ý´½øʼ»¯) */
#define COS_SLIST_REMOVE_HEAD(head, field) do {                \
    COS_SLIST_FIRST((head)) = COS_SLIST_NEXT(COS_SLIST_FIRST((head)), field);    \
} while (0)
#endif

#if CODE_PART("Singly-linked Tail queue")
/*
 * Singly-linked Tail queue declarations.
 */
#define COS_STAILQ_HEAD(name, type)                        \
struct name {                                \
    struct type *stqh_first;/* first element */            \
    struct type **stqh_last;/* addr of last next element */        \
}

#define COS_STAILQ_HEAD_INITIALIZER(head)                    \
    { NULL, &(head).stqh_first }

#define COS_STAILQ_ENTRY(type)                        \
struct {                                \
    struct type *stqe_next;    /* next element */            \
}

/*
 * Singly-linked Tail queue functions.
 */
#define COS_STAILQ_EMPTY(head)    ((head)->stqh_first == NULL)

#define COS_STAILQ_ENTRY_EMPTY(head, elm, field)  (((elm)->field.stqe_next == NULL) && ((head)->stqh_last != &COS_STAILQ_NEXT((elm), field)))

#define COS_STAILQ_ENTRY_INIT(elm, field) do {    \
    (elm)->field.stqe_next = NULL;    \
} while (0)

#define COS_STAILQ_FIRST(head)    ((head)->stqh_first)

#define COS_STAILQ_FOREACH(var, head, field)                \
    for((var) = COS_STAILQ_FIRST((head));                \
       (var);                            \
       (var) = COS_STAILQ_NEXT((var), field))

#define COS_STAILQ_INIT(head) do {                        \
    COS_STAILQ_FIRST((head)) = NULL;                    \
    (head)->stqh_last = &COS_STAILQ_FIRST((head));            \
} while (0)

#define COS_STAILQ_INSERT_AFTER(head, tqelm, elm, field) do {        \
    if ((COS_STAILQ_NEXT((elm), field) = COS_STAILQ_NEXT((tqelm), field)) == NULL)\
        (head)->stqh_last = &COS_STAILQ_NEXT((elm), field);        \
    COS_STAILQ_NEXT((tqelm), field) = (elm);                \
} while (0)

#define COS_STAILQ_INSERT_HEAD(head, elm, field) do {            \
    if ((COS_STAILQ_NEXT((elm), field) = COS_STAILQ_FIRST((head))) == NULL)    \
        (head)->stqh_last = &COS_STAILQ_NEXT((elm), field);        \
    COS_STAILQ_FIRST((head)) = (elm);                    \
} while (0)

#define COS_STAILQ_INSERT_TAIL(head, elm, field) do {            \
    COS_STAILQ_NEXT((elm), field) = NULL;                \
    COS_STAILQ_LAST((head)) = (elm);                    \
    (head)->stqh_last = &COS_STAILQ_NEXT((elm), field);            \
} while (0)

#define COS_STAILQ_LAST(head)    (*(head)->stqh_last)

#define COS_STAILQ_NEXT(elm, field)    ((elm)->field.stqe_next)

#define COS_STAILQ_REMOVE(head, elm, type, field) do {            \
    if (COS_STAILQ_FIRST((head)) == (elm))    \
    {    \
        COS_STAILQ_REMOVE_HEAD(head, field);            \
    }    \
    else    \
    {    \
        struct type *curelm = COS_STAILQ_FIRST((head));        \
        while (COS_STAILQ_NEXT(curelm, field) != (elm))        \
        {    \
            curelm = COS_STAILQ_NEXT(curelm, field);        \
        }    \
        if ((COS_STAILQ_NEXT(curelm, field) =            \
             COS_STAILQ_NEXT(COS_STAILQ_NEXT(curelm, field), field)) == NULL)    \
        {    \
            (head)->stqh_last = &COS_STAILQ_NEXT((curelm), field);    \
        }    \
    }    \
    COS_STAILQ_ENTRY_INIT((elm), field);    /* ɾ³ýõ¯ */    \
} while (0)

/* ɾ³ýڵã¾³ý´½øʼ»¯) */
#define COS_STAILQ_REMOVE_HEAD(head, field) do {                \
    if ((COS_STAILQ_FIRST((head)) =                    \
         COS_STAILQ_NEXT(COS_STAILQ_FIRST((head)), field)) == NULL)        \
    {    \
        (head)->stqh_last = &COS_STAILQ_FIRST((head));        \
    }    \
} while (0)

/* ɾ³ýdµ½µ±ǰelmµÄùµã¾³ý´½øʼ»¯) */
#define COS_STAILQ_REMOVE_HEAD_UNTIL(head, elm, field) do {            \
    if ((COS_STAILQ_FIRST((head)) = COS_STAILQ_NEXT((elm), field)) == NULL)    \
        (head)->stqh_last = &COS_STAILQ_FIRST((head));        \
} while (0)
#endif

#if CODE_PART("List")
/*
 * List declarations.
 */
#define COS_LIST_HEAD(name, type)                        \
struct name {                                \
    struct type *lh_first;    /* first element */            \
}

#define COS_LIST_HEAD_INITIALIZER(head)                    \
    { NULL }

#define COS_LIST_ENTRY(type)                        \
struct {                                \
    struct type *le_next;    /* next element */            \
    struct type **le_prev;    /* address of previous next element */    \
}

/*
 * List functions.
 */

#define COS_LIST_EMPTY(head)    ((head)->lh_first == NULL)

#define COS_LIST_ENTRY_EMPTY(elm, field)    (((elm)->field.le_next == NULL) && ((elm)->field.le_prev == NULL))

#define COS_LIST_ENTRY_INIT(elm, field) do {    \
    (elm)->field.le_next = NULL;    \
    (elm)->field.le_prev = NULL;    \
} while (0)

#define COS_LIST_FIRST(head)    ((head)->lh_first)

#define COS_LIST_FOREACH(var, head, field)                    \
    for ((var) = COS_LIST_FIRST((head));                \
        (var);                            \
        (var) = COS_LIST_NEXT((var), field))

/* ´ӱävar¿ªʼ±é */
#define COS_LIST_FOREACH_FROM_ELM(elm, field)    \
    for (;    \
        (elm);    \
        (elm) = COS_LIST_NEXT((elm), field))

#define COS_LIST_FOREACH_SAFE(var, head, field, tvar)    \
    for ((var) = COS_LIST_FIRST((head));    \
        (var) ? (((tvar) = COS_LIST_NEXT((var), field)), TRUE) : FALSE;    \
        (var) = (tvar))

/* ´ӱävar¿ªʼ°²ȫ±é */
#define COS_LIST_FOREACH_SAFE_FROM_ELM(elm, field, telm)    \
    for (;    \
        (elm) ? (((telm) = COS_LIST_NEXT((elm), field)), TRUE) : FALSE;    \
        (elm) = (telm))

#define COS_LIST_INIT(head) do {                        \
    COS_LIST_FIRST((head)) = NULL;                    \
} while (0)

#define COS_LIST_INSERT_AFTER(listelm, elm, field) do {            \
    if ((COS_LIST_NEXT((elm), field) = COS_LIST_NEXT((listelm), field)) != NULL)\
        COS_LIST_NEXT((listelm), field)->field.le_prev =        \
            &COS_LIST_NEXT((elm), field);                \
    COS_LIST_NEXT((listelm), field) = (elm);                \
    (elm)->field.le_prev = &COS_LIST_NEXT((listelm), field);        \
} while (0)

#define COS_LIST_INSERT_BEFORE(listelm, elm, field) do {            \
    (elm)->field.le_prev = (listelm)->field.le_prev;        \
    COS_LIST_NEXT((elm), field) = (listelm);                \
    *(listelm)->field.le_prev = (elm);                \
    (listelm)->field.le_prev = &COS_LIST_NEXT((elm), field);        \
} while (0)

#define COS_LIST_INSERT_HEAD(head, elm, field) do {                \
    if ((COS_LIST_NEXT((elm), field) = COS_LIST_FIRST((head))) != NULL)    \
        COS_LIST_FIRST((head))->field.le_prev = &COS_LIST_NEXT((elm), field);\
    COS_LIST_FIRST((head)) = (elm);                    \
    (elm)->field.le_prev = &COS_LIST_FIRST((head));            \
} while (0)

#define COS_LIST_NEXT(elm, field)    ((elm)->field.le_next)

#define COS_LIST_REMOVE(elm, field) do {                    \
    if (COS_LIST_NEXT((elm), field) != NULL)                \
    {    \
        COS_LIST_NEXT((elm), field)->field.le_prev =         \
            (elm)->field.le_prev;                \
    }    \
    *(elm)->field.le_prev = COS_LIST_NEXT((elm), field);        \
    COS_LIST_ENTRY_INIT((elm), field);    /* ɾ³ýõ¯ */    \
} while (0)
#endif

#if CODE_PART("Tail queue")
/*
 * Tail queue declarations.
 */
#define COS_TAILQ_HEAD(name, type)                        \
struct name {                                \
    struct type *tqh_first;    /* first element */            \
    struct type **tqh_last;    /* addr of last next element */        \
}

#define COS_TAILQ_HEAD_INITIALIZER(head)                    \
    { NULL, &(head).tqh_first }

#define COS_TAILQ_ENTRY(type)                        \
struct {                                \
    struct type *tqe_next;    /* next element */            \
    struct type **tqe_prev;    /* address of previous next element */    \
}

/*
 * Tail queue functions.
 */
/* t±í½Ó*/
#define COS_TAILQ_CONCAT(dst_head, src_head, src_field)    do{    \
    if(!COS_TAILQ_EMPTY(src_head))    \
    {    \
        COS_TAILQ_FIRST(src_head)->src_field.tqe_prev = (dst_head)->tqh_last;    \
        *(dst_head)->tqh_last = COS_TAILQ_FIRST(src_head);    \
        (dst_head)->tqh_last = (src_head)->tqh_last;    \
        COS_TAILQ_INIT(src_head);    \
    }    \
}while(0)

#if 0
/* ´Órc_elm½ڵãdst_headt±í½Ó*/
#define TAILQ_CONCAT_FROM_ELM(dst_head, src_head, src_elm, src_field)    do{    \
    VOID **__prev_next = (src_elm)->src_field.tqe_prev;    /* Ô´æc_elmµÄ°һ½ڵãtqe_nextµØ· */\
    *(src_elm)->src_field.tqe_prev = NULL;    \
    (src_elm)->src_field.tqe_prev = (dst_head)->tqh_last;    \
    *(dst_head)->tqh_last = src_elm;    \
    (dst_head)->tqh_last = (src_head)->tqh_last;    \
    (src_head)->tqh_last = __prev_next;    \
}while(0)
#endif

#define COS_TAILQ_EMPTY(head)    ((head)->tqh_first == NULL)

#define COS_TAILQ_ENTRY_EMPTY(elm, field)    (((elm)->field.tqe_next == NULL) && ((elm)->field.tqe_prev == NULL))

#define COS_TAILQ_ENTRY_INIT(elm, field) do {    \
    (elm)->field.tqe_next = NULL;    \
    (elm)->field.tqe_prev = NULL;    \
} while (0)

#define COS_TAILQ_FIRST(head)    ((head)->tqh_first)

#define COS_TAILQ_FOREACH(var, head, field)                    \
    for ((var) = COS_TAILQ_FIRST((head));                \
        (var);                            \
        (var) = COS_TAILQ_NEXT((var), field))

/* ´ӱävar¿ªʼ±é */
#define COS_TAILQ_FOREACH_FROM_ELM(elm, field)    \
    for (;    \
        (elm);    \
        (elm) = COS_TAILQ_NEXT((elm), field))

#define COS_TAILQ_FOREACH_SAFE(var, head, field, tvar)    \
    for ((var) = COS_TAILQ_FIRST((head));    \
        (var) ? (((tvar) = COS_TAILQ_NEXT((var), field)), TRUE) : FALSE;    \
        (var) = (tvar))

/* ´ӱävar¿ªʼ°²ȫ±é */
#define COS_TAILQ_FOREACH_SAFE_FROM_ELM(elm, field, telm)    \
    for (;    \
        (elm) ? (((telm) = COS_TAILQ_NEXT((elm), field)), TRUE) : FALSE;    \
        (elm) = (telm))

#define COS_TAILQ_FOREACH_REVERSE(var, head, headname, field)        \
    for ((var) = COS_TAILQ_LAST((head), headname);            \
        (var);                            \
        (var) = COS_TAILQ_PREV((var), headname, field))

/* ·´Ð°²ȫ±é */
#define COS_TAILQ_FOREACH_REVERSE_SAFE(var, head, headname, field, tvar)    \
    for ((var) = COS_TAILQ_LAST((head), headname);    \
        (var) ? (((tvar) = COS_TAILQ_PREV((var), headname, field)), TRUE) : FALSE;    \
        (var) = (tvar))

#define COS_TAILQ_INIT(head) do {                        \
    COS_TAILQ_FIRST((head)) = NULL;                    \
    (head)->tqh_last = &COS_TAILQ_FIRST((head));            \
} while (0)

#define COS_TAILQ_INSERT_AFTER(head, listelm, elm, field) do {        \
    if (COS_TAILQ_ENTRY_EMPTY((elm), field))            \
    {            \
        if ((COS_TAILQ_NEXT((elm), field) = COS_TAILQ_NEXT((listelm), field)) != NULL)\
            COS_TAILQ_NEXT((elm), field)->field.tqe_prev =         \
                &COS_TAILQ_NEXT((elm), field);                \
        else                                \
            (head)->tqh_last = &COS_TAILQ_NEXT((elm), field);        \
        COS_TAILQ_NEXT((listelm), field) = (elm);                \
        (elm)->field.tqe_prev = &COS_TAILQ_NEXT((listelm), field);        \
    }            \
    else            \
    {            \
        COS_ASSERT(0);            \
    }            \
} while (0)

#define COS_TAILQ_INSERT_BEFORE(listelm, elm, field) do {            \
    if (COS_TAILQ_ENTRY_EMPTY((elm), field))            \
    {            \
        (elm)->field.tqe_prev = (listelm)->field.tqe_prev;        \
        COS_TAILQ_NEXT((elm), field) = (listelm);                \
        *(listelm)->field.tqe_prev = (elm);                \
        (listelm)->field.tqe_prev = &COS_TAILQ_NEXT((elm), field);        \
    }            \
    else            \
    {            \
        COS_ASSERT(0);            \
    }            \
} while (0)

#define COS_TAILQ_INSERT_HEAD(head, elm, field) do {            \
    if (COS_TAILQ_ENTRY_EMPTY((elm), field))            \
    {            \
        if ((COS_TAILQ_NEXT((elm), field) = COS_TAILQ_FIRST((head))) != NULL)    \
            COS_TAILQ_FIRST((head))->field.tqe_prev =            \
                &COS_TAILQ_NEXT((elm), field);                \
        else                                \
            (head)->tqh_last = &COS_TAILQ_NEXT((elm), field);        \
        COS_TAILQ_FIRST((head)) = (elm);                    \
        (elm)->field.tqe_prev = &COS_TAILQ_FIRST((head));            \
    }            \
    else            \
    {            \
        COS_ASSERT(0);            \
    }            \
} while (0)

#define COS_TAILQ_INSERT_TAIL(head, elm, field) do {            \
    if (COS_TAILQ_ENTRY_EMPTY((elm), field))            \
    {            \
        COS_TAILQ_NEXT((elm), field) = NULL;                \
        (elm)->field.tqe_prev = (head)->tqh_last;            \
        *(head)->tqh_last = (elm);                    \
        (head)->tqh_last = &COS_TAILQ_NEXT((elm), field);            \
    }            \
    else            \
    {            \
        COS_ASSERT(0);            \
    }            \
} while (0)

#define COS_TAILQ_LAST(head, headname)                    \
    (*(((struct headname *)((head)->tqh_last))->tqh_last))

#define COS_TAILQ_NEXT(elm, field) ((elm)->field.tqe_next)

#define COS_TAILQ_PREV(elm, headname, field)                \
    ((COS_TAILQ_ENTRY_EMPTY((elm), field)) ? (NULL) :    \
     (*(((struct headname *)((elm)->field.tqe_prev))->tqh_last)))

#define COS_TAILQ_REMOVE(head, elm, field) do {                \
    if (!COS_TAILQ_ENTRY_EMPTY((elm), field))            \
    {            \
        if ((COS_TAILQ_NEXT((elm), field)) != NULL)                \
        {    \
            COS_TAILQ_NEXT((elm), field)->field.tqe_prev =         \
                (elm)->field.tqe_prev;                \
        }    \
        else                                \
        {    \
            (head)->tqh_last = (elm)->field.tqe_prev;        \
        }    \
        *(elm)->field.tqe_prev = COS_TAILQ_NEXT((elm), field);        \
        COS_TAILQ_ENTRY_INIT((elm), field);    /* ɾ³ýõ¯ */    \
    }            \
    else            \
    {            \
        COS_ASSERT(0);            \
    }            \
} while (0)
#endif

#if CODE_PART("Circular queue")
/*
 * Circular queue declarations.
 */
#define COS_CIRCLEQ_HEAD(name, type)                    \
struct name {                                \
    struct type *cqh_first;        /* first element */        \
    struct type *cqh_last;        /* last element */        \
}

#define COS_CIRCLEQ_HEAD_INITIALIZER(head)                    \
    { (VOID *)&(head), (VOID *)&(head) }

#define COS_CIRCLEQ_ENTRY(type)                        \
struct {                                \
    struct type *cqe_next;        /* next element */        \
    struct type *cqe_prev;        /* previous element */        \
}

/*
 * Circular queue functions.
 */
#define COS_CIRCLEQ_EMPTY(head)    ((head)->cqh_first == (VOID *)(head))

#define COS_CIRCLEQ_FIRST(head)    ((head)->cqh_first)

#define COS_CIRCLEQ_FOREACH(var, head, field)                \
    for ((var) = COS_CIRCLEQ_FIRST((head));                \
        (var) != (VOID *)(head);                    \
        (var) = COS_CIRCLEQ_NEXT((var), field))

#define COS_CIRCLEQ_FOREACH_REVERSE(var, head, field)            \
    for ((var) = COS_CIRCLEQ_LAST((head));                \
        (var) != (VOID *)(head);                    \
        (var) = COS_CIRCLEQ_PREV((var), field))

#define COS_CIRCLEQ_INIT(head) do {                        \
    COS_CIRCLEQ_FIRST((head)) = (VOID *)(head);                \
    COS_CIRCLEQ_LAST((head)) = (VOID *)(head);                \
} while (0)

#define COS_CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) do {        \
    COS_CIRCLEQ_NEXT((elm), field) = COS_CIRCLEQ_NEXT((listelm), field);    \
    COS_CIRCLEQ_PREV((elm), field) = (listelm);                \
    if (COS_CIRCLEQ_NEXT((listelm), field) == (VOID *)(head))        \
        COS_CIRCLEQ_LAST((head)) = (elm);                \
    else                                \
        COS_CIRCLEQ_PREV(COS_CIRCLEQ_NEXT((listelm), field), field) = (elm);\
    COS_CIRCLEQ_NEXT((listelm), field) = (elm);                \
} while (0)

#define COS_CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) do {        \
    COS_CIRCLEQ_NEXT((elm), field) = (listelm);                \
    COS_CIRCLEQ_PREV((elm), field) = COS_CIRCLEQ_PREV((listelm), field);    \
    if (COS_CIRCLEQ_PREV((listelm), field) == (VOID *)(head))        \
        COS_CIRCLEQ_FIRST((head)) = (elm);                \
    else                                \
        COS_CIRCLEQ_NEXT(COS_CIRCLEQ_PREV((listelm), field), field) = (elm);\
    COS_CIRCLEQ_PREV((listelm), field) = (elm);                \
} while (0)

#define COS_CIRCLEQ_INSERT_HEAD(head, elm, field) do {            \
    COS_CIRCLEQ_NEXT((elm), field) = COS_CIRCLEQ_FIRST((head));        \
    COS_CIRCLEQ_PREV((elm), field) = (VOID *)(head);            \
    if (COS_CIRCLEQ_LAST((head)) == (VOID *)(head))            \
        COS_CIRCLEQ_LAST((head)) = (elm);                \
    else                                \
        COS_CIRCLEQ_PREV(COS_CIRCLEQ_FIRST((head)), field) = (elm);    \
    COS_CIRCLEQ_FIRST((head)) = (elm);                    \
} while (0)

#define COS_CIRCLEQ_INSERT_TAIL(head, elm, field) do {            \
    COS_CIRCLEQ_NEXT((elm), field) = (VOID *)(head);            \
    COS_CIRCLEQ_PREV((elm), field) = COS_CIRCLEQ_LAST((head));        \
    if (COS_CIRCLEQ_FIRST((head)) == (VOID *)(head))            \
        COS_CIRCLEQ_FIRST((head)) = (elm);                \
    else                                \
        COS_CIRCLEQ_NEXT(COS_CIRCLEQ_LAST((head)), field) = (elm);    \
    COS_CIRCLEQ_LAST((head)) = (elm);                    \
} while (0)

#define COS_CIRCLEQ_LAST(head)    ((head)->cqh_last)

#define COS_CIRCLEQ_NEXT(elm,field)    ((elm)->field.cqe_next)

#define COS_CIRCLEQ_PREV(elm,field)    ((elm)->field.cqe_prev)

#define COS_CIRCLEQ_REMOVE(head, elm, field) do {                \
    if (COS_CIRCLEQ_NEXT((elm), field) == (VOID *)(head))        \
        COS_CIRCLEQ_LAST((head)) = COS_CIRCLEQ_PREV((elm), field);    \
    else                                \
        COS_CIRCLEQ_PREV(COS_CIRCLEQ_NEXT((elm), field), field) =    \
            COS_CIRCLEQ_PREV((elm), field);                \
    if (COS_CIRCLEQ_PREV((elm), field) == (VOID *)(head))        \
        COS_CIRCLEQ_FIRST((head)) = COS_CIRCLEQ_NEXT((elm), field);    \
    else                                \
        COS_CIRCLEQ_NEXT(COS_CIRCLEQ_PREV((elm), field), field) =    \
            COS_CIRCLEQ_NEXT((elm), field);                \
} while (0)
#endif

#if CODE_PART("Double Circular queue")

typedef struct cos_dcq_node
{
    struct cos_dcq_node *prev;
    struct cos_dcq_node *next;
}COS_DCQ_NODE_T;
typedef struct cos_dcq_node COS_DCQ_HEAD_T;


#define COS_DCQ_HEAD_INIT(HEAD)\
do{\
    (HEAD)->prev = (HEAD)->next = HEAD;\
}while(0)

#define COS_DCQ_NODE_INIT(NODE)\
do{\
    (NODE)->prev = (NODE)->next = NODE;\
}while(0)


#define COS_DCQ_IS_EMPTY(HEAD)  (((HEAD)->prev == HEAD) && ((HEAD)->next == HEAD))


#define COS_DCQ_NODE_AlONE(NODE)  (((NODE)->prev == NODE) && ((NODE)->next == NODE))


#define COS_DCQ_INSERT(NODE,PREV,NEXT)\
do{\
    (PREV)->next = NODE;\
    (NEXT)->prev = NODE;\
    (NODE)->prev = PREV;\
    (NODE)->next = NEXT;\
}while(0)


#define COS_DCQ_INSERT_TAIL(HEAD,NODE)\
do{\
    COS_ASSERT((HEAD)->next != NULL);\
    COS_ASSERT((HEAD)->prev != NULL);\
    COS_ASSERT((NODE)->next != NULL);\
    COS_ASSERT((NODE)->prev != NULL);\
    if(COS_DCQ_NODE_AlONE(NODE))\
    {\
        (HEAD)->prev->next = NODE;\
        (NODE)->prev = (HEAD)->prev;\
        (HEAD)->prev = NODE;\
        (NODE)->next = HEAD;\
    }\
    else\
    {\
        COS_ASSERT(0);\
    }\
}while(0)


#define COS_DCQ_INSERT_HEAD(HEAD,NODE)\
do{\
    COS_ASSERT((NODE)->next != NULL);\
    COS_ASSERT((NODE)->prev != NULL);\
    if(COS_DCQ_NODE_AlONE(NODE))\
    {\
        (HEAD)->next->prev = NODE;\
        (NODE)->prev = (HEAD)->next;\
        (HEAD)->next = NODE;\
        (NODE)->next = HEAD;\
    }\
    else\
    {\
        COS_ASSERT(0);\
    }\
}while(0)


#define COS_DCQ_REMOVE(NODE)\
do{\
    COS_ASSERT((NODE)->next != NULL);\
    COS_ASSERT((NODE)->prev != NULL);\
    (NODE)->prev->next = (NODE)->next;\
    (NODE)->next->prev = (NODE)->prev;\
    (NODE)->next = NODE;\
    (NODE)->prev = NODE;\
}while(0)


#define COS_DCQ_CONCAT(DHEAD,SHEAD)\
do{\
    COS_ASSERT((DHEAD)->next != NULL);\
    COS_ASSERT((DHEAD)->prev != NULL);\
    COS_ASSERT((SHEAD)->next != NULL);\
    COS_ASSERT((SHEAD)->prev != NULL);\
    if(!COS_DCQ_IS_EMPTY(SHEAD))\
    {\
        (DHEAD)->prev->next = (SHEAD)->next;\
        (SHEAD)->prev->next = (DHEAD);\
        (SHEAD)->next->prev = (DHEAD)->prev;\
        (DHEAD)->prev = (SHEAD)->prev;\
        (SHEAD)->next = (SHEAD);\
        (SHEAD)->prev = (SHEAD);\
    }\
}while(0)


#define COS_DCQ_FOREACH(NODE,HEAD)\
for ((NODE) = (HEAD)->next; (NODE) != (HEAD); (NODE) = (NODE)->next)


#define COS_DCQ_FOREACH_SAFE(NODE, HEAD, NEXT) \
for ((NODE) = (HEAD)->next, (NEXT) = (NODE)->next; (NODE) != (HEAD); (NODE) = (NEXT), (NEXT) = (NODE)->next)


#define COS_DCQ_REVERSE(NODE,HEAD)\
for ((NODE) = (HEAD)->prev; (NODE) != (HEAD); (NODE) = (NODE)->prev)


#define COS_DCQ_REVERSE_SAFE(NODE,HEAD,NEXT)\
for ((NODE) = (HEAD)->prev,(NEXT) = (NODE)->prev; (NODE) != (HEAD); (NODE) = (NEXT), (NEXT) = (NODE)->prev)

#define COS_DCQ_FIRST(HEAD) (((HEAD)->next == (HEAD))?NULL:(HEAD)->next)
#endif

 #if CODE_PART("MANAGEMENT CONFIGURE")
 #define ODT_MP_BEGIN                         (WORD32)0x0000a000
 #define ODT_MP_ALARM_MGR_CUR_ALARM           (WORD32)0x0000a001
 #define ODT_MP_WCONFD_MIDDLEWARE             (WORD32)0x0000a002
 #define ODT_MP_CONFDHA_CTRL                  (WORD32)0x0000a003
  #define ODT_MP_CONFD_PROXY                  (WORD32)0x0000a004
 #define ODT_MP_END                           (WORD32)0x0000afff
 #endif

#endif



