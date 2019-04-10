#ifndef _SOCKETS_H_
#define _SOCKETS_H_

typedef struct socket_info socket_info;
typedef void (*connection_handler)(socket_info*); // takes 

#define SOCK_DEBUG_MESSAGES 1

struct socket_info* socket_create();
void socket_free(socket_info* sockInfo);

void socket_connect(socket_info* info, int port);
void socket_bind_and_listen(socket_info* sockInfo, int port, void* handler);

int socket_send(socket_info* sock, char* msg, int msg_len);
int socket_read(socket_info* sock, char* buffer, int buffer_len);




#endif