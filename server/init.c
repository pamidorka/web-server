
#include "headers/http.h"

SERV* http_server_init(
    const char* ip_addr, 
    uint16_t port, 
    uint16_t client_num, 
    cather cather_func) 
{

    SERV* new_server = malloc(sizeof(SERV));

    new_server->status = 1;

    new_server->net.sin_port = htons(port);

    new_server->sock = socket(AF_INET, SOCK_STREAM, 0);
    new_server->net_len = sizeof(new_server->net);

    if (!inet_aton(ip_addr, &(new_server->net.sin_addr))) {
        http_error("inet_aton");
        free(new_server);
        return NULL;
    }

    if (bind(new_server->sock, 
        (struct sockaddr*)&(new_server->net), 
        new_server->net_len) < 0) 
    {
        http_error("bind");
        free(new_server);
        return NULL;
    }

    if (listen(new_server->sock, client_num) < 0) {
        http_error("listen");
        free(new_server);
        return NULL;
    }

    for (uint8_t i = 0; i < HTTP_THREADS; i++) {
        pthread_create(&(new_server->pid[i]), NULL, cather_func, new_server);
    }

    http_log(new_server, "server start");

    return new_server;
}

void http_server_wait(SERV* server) {
    for (uint8_t i = 0; i < HTTP_THREADS; i++) {
        pthread_join(server->pid[i], NULL);
    }
    http_log(server, "server stop");
}
