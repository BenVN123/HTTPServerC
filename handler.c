#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "handler.h"

void handle_connection(int socket) {
    char request[2048] = "";
    int valread = read(socket, request, 2048);

    if (valread < 0) {
        perror("empty request");
    }
    printf("%s\n", request);

    char *response = generate_response(request);
    write(socket, response, strlen(response));   

    free(response);
    close(socket);
}

void error_message(char *response) {
    strncpy(response, "HTTP/1.1 404 NOT FOUND\n\n<p>not found</p>\0", 41);
}

void success_message(char *path, char *response) {
    if (strncmp(path, "/", strlen(path)) == 0) {
        strncpy(response, "HTTP/1.1 200 OK\n\n<p>index</p>\0", 30);
    } else if (strncmp(path, "/home", strlen(path)) == 0) {
        strncpy(response, "HTTP/1.1 200 OK\n\n<p>home</p>\0", 29);
    } else {
        error_message(response);
    }
}

char* generate_response(char request[]) {
    char *response = malloc(sizeof(char) * 2048);
   
    char *method_ptr = request;
    char *path_ptr = strchr(request, ' ') + 1;
    char *end_of_path_ptr = strchr(path_ptr, ' ');
    
    size_t method_len = path_ptr - request - 1;
    size_t path_len = end_of_path_ptr - path_ptr;

    char *method = malloc(sizeof(char) * (method_len + 1));
    char *path = malloc(sizeof(char) * (path_len + 1));

    strncpy(method, method_ptr, method_len);
    strncpy(path, path_ptr, path_len);

    method[method_len] = '\0';
    path[path_len] = '\0';
    
    if (strncmp(method, "GET", strlen(method)) != 0) {
        error_message(response);
    } else {
        success_message(path, response);
    }
    
    free(method);
    free(path);
    return response;
}
