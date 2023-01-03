
#include "headers/http.h"
#include "headers/analyzer.h"

int http_analyzer(USR* client) {

    if (!client) {
        http_error("client was null");
        return 1;
    }

    FILE* client_stream = fdopen(client->sock, "r");

    char buf[READER_BUF];

    while (fgets(buf, READER_BUF, client_stream)) {
        printf("%s", buf);
    }
    printf("\n");

}