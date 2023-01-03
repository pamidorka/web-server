
#include <stdio.h>
#include <malloc.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HTTP_THREADS 5

#define ERROR 
#define LOG

#ifdef ERROR 
#define http_error(str) \
    printf( \
        "ERROR: "str"\n" \
        "  in %s():%d\n", \
        __func__, \
        __LINE__ \
    ); \
    perror("  ")
#else 
#define http_error(str)
#endif

#ifdef LOG
#define http_log(user, event) \
    fprintf( \
        stdout, \
        "LOG:\n" \
        "  ip %s\n" \
        "  port %d\n" \
        "  "event"\n", \
        inet_ntoa(user->net.sin_addr), \
        ntohs(user->net.sin_port) \
    ) 
#define http_log_nu(event) \
    fprintf ( \
        stdout, \
        "LOG: "event"\n" \
    )
#else
http_log(user, event)
#endif

typedef int http_t;

typedef struct server {
    struct sockaddr_in net;
    socklen_t net_len;
    pthread_t pid[HTTP_THREADS];
    http_t sock;
    uint8_t status;
} SERV;

typedef struct user {
    struct sockaddr_in net;
    socklen_t net_len;
    http_t sock;
} USR;
