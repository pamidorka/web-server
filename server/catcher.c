
#include "headers/http.h"
#include "headers/analyzer.h"

#include <unistd.h>

pthread_mutex_t catcher_mutex;

void http_catcher(SERV* server) {

    if (!server) {
        http_error("server was null");
        return;
    }

    http_log_nu("thread start!");

    while (server->status) {
        USR* new_user = malloc(sizeof(USR));

        pthread_mutex_lock(&catcher_mutex);
        new_user->sock = accept(server->sock, 
                                (struct sockaddr*)&(new_user->net), 
                                &(new_user->net_len));
        pthread_mutex_unlock(&catcher_mutex);

        http_log(new_user, "the user connect to server");

        if (http_analyzer(new_user)) {
            http_error("http_analyzer");
        }

        close(new_user->sock);

        free(new_user);
    }

    http_log_nu("thread stop.");

}

void http_catcher_stop(SERV* server) {
    http_log_nu("server stoping...");
    server->status = 0;
}