#ifdef __linux__
#include <sys/socket.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include "sockets.h"
#include "sock_internal.h"
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <netdb.h>


struct socket_info* socket_create() {
    struct socket_info* sockInfo = malloc(sizeof(struct socket_info));

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == -1) {
        if(SOCK_DEBUG_MESSAGES) perror("Socket");
        return NULL;
    }
    sockInfo->socketFD = socketFD;

    return sockInfo;
}

static void socket_accept_in_new_thread(int sockFD, struct sockaddr_in client, int length, void* conn_handler) {
    struct socket_info* inf = malloc(sizeof(struct socket_info));
    inf->socketFD = sockFD;

    connection_handler handler = (connection_handler) conn_handler;
    handler(inf);
}

void socket_bind_and_listen(struct socket_info* sockInfo, int port, void* conn_handler) {
    struct sockaddr_in addr;

    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    int bindRet = bind(sockInfo->socketFD, (const struct sockaddr*)&addr, sizeof(struct sockaddr));
    if(bindRet < 0) {
        if(SOCK_DEBUG_MESSAGES) perror("Bind");
        return;
    }

    int listenRet = listen(sockInfo->socketFD, 20);
    if(listenRet < 0) {
        if(SOCK_DEBUG_MESSAGES) perror("Listen");
        return;
    }

    printf("Listening to sockets...\n");


    int running = 1;
    while(running) {
        struct sockaddr_in addr_peer;
        int length = sizeof(addr_peer);
        if(SOCK_DEBUG_MESSAGES) printf("Listening to another socket\n");
        int newSock = accept(sockInfo->socketFD, (struct sockaddr*) &addr_peer, (socklen_t*) &length);
        if(SOCK_DEBUG_MESSAGES) printf("Got a new socket\n");
        socket_accept_in_new_thread(newSock, addr_peer, length, conn_handler);
    }
}   // SOCKET BIND AND LISTEn



void socket_connect(struct socket_info* info, int port) {
    struct sockaddr_in client_addr;
    struct hostent* host = gethostbyname("localhost");

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    memcpy(&client_addr.sin_addr, host->h_addr_list[0], sizeof(client_addr.sin_addr));


    int connectRet = connect(info->socketFD, (const struct sockaddr*) &client_addr, (socklen_t) sizeof(client_addr)); 
    if(connectRet < 0) {
        if(SOCK_DEBUG_MESSAGES) perror("Connect");
        return;
    }
} // socket connect

int socket_send(struct socket_info* sock, char* msg, int msg_len) {
    int sendRet = send(sock->socketFD, msg, msg_len, MSG_NOSIGNAL);
    if(sendRet == -1) {
        if(SOCK_DEBUG_MESSAGES) perror("Send");
        return -1;
    }
    return sendRet;
}

int socket_read(struct socket_info* sock, char* buffer, int buffer_len) {
    int recvRet = recv(sock->socketFD, buffer, buffer_len, 0); 
    if(recvRet == -1) {
        if(SOCK_DEBUG_MESSAGES) perror("Recv");
        return -1;
    }
    return recvRet;
}

void socket_free(struct socket_info* sockInfo) {
    // ... do some more code
    close(sockInfo->socketFD);
    free(sockInfo);
}



#endif
