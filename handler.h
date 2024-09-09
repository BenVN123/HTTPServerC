#ifndef __HANDLER__
#define __HANDLER__

void handle_connection(int socket);
void error_message(char *response);
void success_message(char *path, char *response);
char* generate_response(char *request);

#endif
