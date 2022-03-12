#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

int main(int argc, char *argv[]){
    char *message;
    char *response;
    int sockfd;

    char *host = "34.118.48.238";

    
    char *str = malloc(sizeof (char *));
    char buffer[BUFLEN];
    char *cookie = (char*)malloc(500);
    char *cookie2 = (char*)malloc(500);
    char *token = (char*)malloc(500);
    char *token2 = (char*)malloc(500);


while(1){
    scanf("%s", str);

    if(strcmp(str, "register") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM,0);
        char username[17];
        char password[17];

        printf("username=");
        scanf("%s", username);
        printf("password=");
        scanf("%s", password);

        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);

        json_object_set_string(root_object,"username", username);
        json_object_set_string(root_object,"password", password);


        message = compute_post_request(host,"/api/v1/tema/auth/register","application/json", root_value, 2, NULL, NULL);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        //printf("%s\n", response);

        if(strstr(response, "error") != NULL) {
            char *tok;
            char aux[200];
            char *error_msg;

            memset(buffer, 0, BUFLEN);
            strcpy(buffer, response);
        
            tok = strtok(buffer, "\n");
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);
        }else{
            printf("Registration completed successfully!\n");
        }

    close_connection(sockfd);
    }

    if(strcmp(str, "login") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM,0);
        char username[17];
        char password[17];

        printf("username=");
        scanf("%s", username);
        printf("password=");
        scanf("%s", password);

        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);

        json_object_set_string(root_object,"username", username);
        json_object_set_string(root_object,"password", password);


        message = compute_post_request(host,"/api/v1/tema/auth/login","application/json", root_value, 2, NULL, NULL);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
       // printf("%s\n", response);

        if(strstr(response, "error") != NULL) {
            char *tok;
            char aux[200];
            char *error_msg;

            memset(buffer, 0, BUFLEN);
            strcpy(buffer, response);
        
            tok = strtok(buffer, "\n");
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    //printf("%s\n", aux);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);

        }else{
            printf("Login completed successfully!\n");

        char *tok;
        char aux[200];    

        
        memset(buffer, 0, BUFLEN);
        strcpy(buffer, response);
        
        tok = strtok(buffer, "\n");
        while(tok != NULL){
            if(strncmp(tok, "Set-Cookie:", 11) == 0){
                strcpy(aux, tok);
                break;
            }
            tok = strtok (NULL, "\n");
        }

        cookie = strtok(aux, " ");

        cookie = strtok(NULL, " ");
        cookie[strlen(cookie) - 1] = 0;

        strcpy(cookie2, cookie);
        //printf("%s\n", cookie2);
        }
        close_connection(sockfd);

    }

    if(strcmp(str, "enter_library") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);

            message = compute_get_request(host, "/api/v1/tema/library/access", NULL, cookie2, token2);
            //puts(message);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
           // puts(response);

            if(strstr(response, "error") != NULL) {
            char *tok;
            char aux[200];
            char *error_msg;

            memset(buffer, 0, BUFLEN);
            strcpy(buffer, response);
        
            tok = strtok(buffer, "\n");
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);

            }else{
            printf("Access to library granted!\n");
            char *tok;
            char aux[200];
            

            memset(buffer, 0, BUFLEN);
            strcpy(buffer, response);
            
            tok = strtok(buffer, "\n");
            while(tok != NULL){
                if(strstr(tok, "token") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            token = strtok(aux, "\"");
            token = strtok(NULL, "\"");
            token = strtok(NULL, "\"");
            token = strtok(NULL, "\"");
            strcpy(token2,token);


            //printf("%s\n", token);
            }
                
        close_connection(sockfd);
    }

    if(strcmp(str, "get_books") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);
        
        message = compute_get_request(host, "/api/v1/tema/library/books", NULL, cookie2, token2);

       // puts(message);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        //puts(response);
        char *tok;
        char aux[200];
        char *error_msg;

        memset(buffer, 0, BUFLEN);
        strcpy(buffer, response);
        
        tok = strtok(buffer, "\n");

        if(strstr(response, "error") != NULL) {
            
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);

        }else{
            printf("Library has following books:\n");
            while(tok != NULL){
                if(strstr(tok, "title") != NULL){
                    strcpy(aux, tok);
                    break;
            }
                tok = strtok (NULL, "\n");
            }
            
            printf("%s\n", aux);
        }

        close_connection(sockfd);
    }

    if(strcmp(str, "get_book") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);
       
        char id[4];

        printf("id=");
        scanf("%s", id);

        char buf[35];
        snprintf(buf, sizeof(buf), "%s%s", "/api/v1/tema/library/books/", id);

        message = compute_get_request(host, buf, NULL, cookie2, token2);

        //puts(message);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
       // puts(response);

        char *tok;
        char aux[200];
        char *error_msg;

        memset(buffer, 0, BUFLEN);
        strcpy(buffer, response);
        
        tok = strtok(buffer, "\n");

        if(strstr(response, "error") != NULL) {
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);

        }else {
            printf("Request executed successfully:\n");
            while(tok != NULL){
                if(strstr(tok, "title") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            printf("%s\n", aux);
        }

        close_connection(sockfd);
    }

    if(strcmp(str, "add_book") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);
        char title[17];
        char author[17];
        char genre[17];
        char publisher[17];
        char page_count[3];

        printf("title=");
        scanf("%s", title);
        printf("author=");
        scanf("%s", author);
        printf("genre=");
        scanf("%s", genre);
        printf("publisher=");
        scanf("%s", publisher);
        printf("page_count=");
        scanf("%s", page_count);

        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);

        json_object_set_string(root_object,"title", title);
        json_object_set_string(root_object,"author", author);
        json_object_set_string(root_object,"genre", genre);
        json_object_set_string(root_object,"publisher", publisher);
        json_object_set_string(root_object,"page_count", page_count);
       
        message = compute_post_request(host, "/api/v1/tema/library/books", "application/json", root_value, 5, NULL, token2);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        //printf("%s\n", response);
        char *tok;
        char aux[200];
        char *error_msg;

        memset(buffer, 0, BUFLEN);
        strcpy(buffer, response);
        
        tok = strtok(buffer, "\n");
        if(strstr(response, "error") != NULL) {
            
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg[strlen(error_msg) - 1] = 0;
            printf("%s\n", error_msg);
        }else{
            printf("Book [%s] has been successfully added to library!\n", title);
        }

        close_connection(sockfd);
    }

    if(strcmp(str, "delete_book") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM, 0);
        char id[4];
        printf("id=");
        scanf("%s", id);
        char buf[35];
        snprintf(buf, sizeof(buf), "%s%s", "/api/v1/tema/library/books/", id);

        message = compute_get_request(host, buf, NULL, cookie2, token2);

        //puts(message);
        send_to_server(sockfd, message);
        response = receive_from_server(sockfd);
        //puts(response);

        char *tok;
        char aux[200];
        char *error_msg;

        memset(buffer, 0, BUFLEN);
        strcpy(buffer, response);
        
        tok = strtok(buffer, "\n");
        if(strstr(response, "error") != NULL) {
           
            while(tok != NULL){
                if(strstr(tok, "error") != NULL){
                    strcpy(aux, tok);
                    break;
                }
                tok = strtok (NULL, "\n");
            }
            
            error_msg = strtok(aux, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            error_msg = strtok(NULL, "\"");
            printf("%s\n", error_msg);
        }else{
            printf("Book deleted successfully!\n");
        }

        close_connection(sockfd);
    }
       

    if(strcmp(str, "logout") == 0){
        sockfd = open_connection(host, 8080, AF_INET, SOCK_STREAM,0);
        if(cookie2 == NULL){
            printf("User not logged in!\n");
            }else{
            message = compute_get_request(host, "/api/v1/tema/auth/logout", NULL, cookie2, NULL);
           // printf("%s\n", response);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            printf("User logged out successfully!\n");
        }
        close_connection(sockfd);
    }

    if(strcmp(str, "exit") == 0){
        exit(0);
    }

}

    close_connection(sockfd);
    // free the allocated data at the end
    free(str);
    free(cookie);
    free(cookie2);
    free(token);
    free(token2);

    return 0;
}
