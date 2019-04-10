#include <stdio.h>
#include <stdlib.h> 

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#include <dirent.h>
#include <pthread.h>
#endif
#include "sockets.h"
#include <string.h>

void communication_start();

int main() {
	communication_start();
	return 0;

	void* sock_info = socket_create();
	socket_connect(sock_info, 5555);

	char msg[] = "Retard";
	char* buffer = malloc(1024);

	socket_send(sock_info, msg, strlen(msg));
	socket_read(sock_info, buffer, 1024);

	printf("Message received: %s\n", buffer);

    return 0;
}

void communication_start() {
    printf("Starting communication\n");
	void* client = socket_create();
    printf("Connecting\n");
	socket_connect(client, 5555);

	// echo server
    // alocate needed resources
    int running = 1;
    char* buffer = malloc(1024);
    char* response = malloc(1024);
    int ret; // return value

    while(running) {
        // clear buffers from any data
        printf("Starting loop over\n");
        memset(buffer, 0, 1024);
        memset(response, 0, 1024);

		printf("Introduce message to communicate: ");
		scanf("%s", response);

		ret = socket_send(client, response, 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        printf("Message sent: %s\n", response);


        ret = socket_read(client, buffer, 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        printf("Response received: %s\n", buffer);


    }
    printf("Got out of the main loop, cleaning up\n");


    free(buffer);
    free(response);
    socket_free(client);
}