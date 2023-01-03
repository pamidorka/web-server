
#include "headers/init.h"
#include "headers/catcher.h"

#include <stdlib.h>

int main(void) {
    SERV* server = http_server_init("0.0.0.0", 80, 5, http_catcher);
    if (!server) {
        exit(EXIT_FAILURE);
    }
    http_server_wait(server);
    
    exit(EXIT_SUCCESS);
}