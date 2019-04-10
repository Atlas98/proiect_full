#include <internal.h>
#if NETWORKING_MODULE_ENABLED
#include "sockets/sockets.h"
#include "message_handler.h"

#include <exports.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#include <data/data.h>
#include <structs.h>
#include <malloc.h>

// no usage, tells me if shit is happening in a thread or not
#define _thread

/* client is malloc'd, must be freed after use */
INTERNAL_FUNCTION _thread void* handle_by_thread(void* client) {
    printf("Started threaded execution\n");
    pthread_detach(pthread_self());
    
    // Maintains a connection with the client, exchanging informations about the data 
    // alocate needed resources
    int running = 1;
    char buffer[1024];
    char response[1024];
    int ret;

    // each connection has it's data 
    struct data data;
    int stage = 0;

    while(running) {
        // clear buffers from any data
        memset(&buffer, 0, 1024);
        memset(&response, 0, 1024);

        
        ret = socket_read(client, &buffer[0], 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        if(ret != 0) {
            printf("Message read: %s\n", &buffer);
            handle_message(&data, &buffer[0], &response[0], &stage);
        }
        
        ret = socket_send(client, &response[0], 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        printf("Message sent: %s\n", response);
        
    }
    
    printf("Got out of the main loop\n");

    socket_free(client);

    return NULL;
}




/* This functions creates the threads */
INTERNAL_FUNCTION void handler_func(socket_info* client) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    size_t stacksize;
    stacksize = (double) 16*1024;
    pthread_attr_setstacksize (&attr, stacksize);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t thread0;
    pthread_create(&thread0, &attr, (void*) handle_by_thread, client);
}

// Create server socket and bind
EXPORT_FUNCTION void start_networking_interface() {
    printf("Network interface starting\n");
    mallopt(M_MMAP_THRESHOLD, 0);
    
    struct socket_info* sockInfo = socket_create();
    socket_bind_and_listen(sockInfo, 5555, (void*)handler_func);

    printf("Networking service terminated!\n");
}






#endif