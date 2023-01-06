
#include "headers/http.h"

#include <string.h>

int http_sender(USR* restrict client, CLB* restrict callback) {

    if (send(client->sock, callback->http_hdr, callback->hdr_size, 0) < 0) {
        http_error("send");
    }

    char buf[READER_BUF];

    memset(buf, 0x0, READER_BUF);
    while (fgets(buf, READER_BUF, callback->file)) {
        if (send(client->sock, buf, strlen(buf), 0) < 0) {
            http_error("send");
        }
        memset(buf, 0x0, READER_BUF);
    }

    return 0;
}