
#include <stdint.h>
#include <malloc.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
    fprintf( \
        stdout, \
        "LOG: "event"\n" \
    )
#define http_log_va(user, event, ...) \
    fprintf( \
        stdout, \
        "LOG:\n" \
        "  ip %s\n" \
        "  port %d\n" \
        "  "event"\n", \
        inet_ntoa(user->net.sin_addr), \
        ntohs(user->net.sin_port), \
        ##__VA_ARGS__ \
    ) 
#define http_log_nu_va(event, ...) \
    fprintf( \
        stdout, \
        "LOG: "event"\n", \
        ##__VA_ARGS__ \
    )
#else
http_log(user, event)
#endif

#define HTTP_THREADS            5
#define READER_BUF              64

#define GET                     "GET"
#define HTTP_V                  "HTTP/1.1"
#define STATUS_CODE_SUCCSESS    "200"
#define OK                      "OK"
#define CONTENT_TYPE            "Content-type:"
#define TEXT                    "text/"
#define HTML                    "html"
#define NEW_LINE                "\n"

#define TWO_NEW_LINE            NEW_LINE \
                                NEW_LINE

#define STD_HDR                 HTTP_V" " \
                                STATUS_CODE_SUCCSESS" " \
                                OK \
                                NEW_LINE

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

typedef struct callback {
    char* http_hdr;
    size_t hdr_size;
    FILE* file;
} CLB;

typedef void(*cather)(SERV*);