
#include <stdint.h>

typedef struct user USR;
typedef struct server SERV;
typedef void(*cather)(SERV*);

SERV* http_server_init(
    const char* ip_addr, 
    uint16_t port, 
    uint16_t client_num, 
    cather cather_func);

void http_server_wait(SERV* server);