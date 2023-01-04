
#include "headers/http.h"

#include <string.h>

int http_sender(USR* restrict client, CLB* restrict callback) {

    if (send(client->sock, callback->http_hdr, callback->hdr_size, 0) < 0) {
        http_error("send");
    }

    http_log_nu_va("sender send %s", callback->http_hdr);

    char buf[READER_BUF];

    memset(buf, 0, READER_BUF);
    while (fgets(buf, READER_BUF, callback->file)) {
        if (send(client->sock, buf, READER_BUF, 0) < 0) {
            http_error("send");
        }
        memset(buf, 0, READER_BUF);
    }

    return 0;
}