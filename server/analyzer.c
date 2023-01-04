
#include "headers/http.h"
#include "headers/sender.h"

#include <string.h>

struct user_call {
    char* method;
    char* file_name;
    char* http_v;
};

static inline struct user_call* parse_hdr(char* hdr) {
    struct user_call* call = malloc(sizeof(struct user_call));

    char* curr_str = strtok(hdr, " ");

    call->method = malloc(sizeof(char) * strlen(curr_str));
    strcpy(call->method, curr_str);

    curr_str = strtok(NULL, " ");

    call->file_name = malloc(sizeof(char) * strlen(curr_str) + 1);
    strcpy(call->file_name, ".");
    strcat(call->file_name, curr_str);

    curr_str = strtok(NULL, " ");

    call->http_v = malloc(sizeof(char) * strlen(curr_str));
    strcpy(call->http_v, curr_str);

    return call;
}

static inline CLB* create_callback(struct user_call* call) {
    CLB* clb = malloc(sizeof(CLB));

    clb->hdr_size = sizeof(STD_HDR);

    if (strstr(call->file_name, HTML)) {

        clb->hdr_size += sizeof(CONTENT_TYPE " " TEXT HTML TWO_NEW_LINE);

        clb->file = fopen(call->file_name, "r");

        clb->http_hdr = malloc(sizeof(char) * clb->hdr_size);

        strcpy(clb->http_hdr, STD_HDR);
        strcat(clb->http_hdr, CONTENT_TYPE " " TEXT HTML TWO_NEW_LINE);
    }
    else {
        free(clb);
        clb = NULL;
    }

    if (!clb->file) {
        http_error("file was null (not found)");
        free(clb);
        clb = NULL;
    }

    return clb; 
}

int http_analyzer(USR* client) {

    if (!client) {
        http_error("client was null");
        return 1;
    }

    FILE* client_stream = fdopen(client->sock, "r");

    char buf[READER_BUF];
    fgets(buf, READER_BUF, client_stream);
    
    struct user_call* u_call = parse_hdr(buf);

    if (!u_call) {
        http_error("user call was null");
        return 1;
    }

    http_log_va(client, "the client ask for this data %s", u_call->file_name);

    CLB* clb = create_callback(u_call);

    free(u_call);

    if (!clb) {
        http_error("callback was null");
        return 1;
    }

    return http_sender(client, clb);
}