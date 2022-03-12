#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

char *compute_get_request(char *host, char *url, char *query_params, char *cookie, char *token){
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);
    sprintf(line, "Host: %s", host);

    compute_message(message, line);
    sprintf(line, "Cookie: %s", cookie);

    compute_message(message,line);
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);

    compute_message(message, "");
    return message;
}

char *compute_post_request(char *host, char *url, char* content_type, JSON_Value *root_value,
                            int body_data_fields_count, char *cookie, char *token){
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    

    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    sprintf(line,"Content-Type: %s", content_type);
    compute_message(message, line);
    
    char *serialized_string = NULL;

    serialized_string = json_serialize_to_string_pretty(root_value);
    int count = strlen(serialized_string);

    sprintf(line, "Content-Length: %d", count);
    compute_message(message, line);

    sprintf(line, "Cookie: %s", cookie);
    compute_message(message, line);

    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);
    compute_message(message, "");

    strcpy(body_data_buffer,serialized_string);

    memset(line, 0, LINELEN);
    compute_message(message, body_data_buffer);

    free(line);
    return message;
}

char *compute_delete_request(char *host, char *url, char *query_params, char *cookie, char *token){
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }

    compute_message(message, line);

    
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    sprintf(line, "Cookie: %s", cookie);

    compute_message(message,line);
    
    sprintf(line, "Authorization: Bearer %s", token);
    compute_message(message, line);

    compute_message(message, "");
    return message;
}


