#include "sockets/sockets.h"
#include "networking_interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#include "../structs.h"
#include <malloc.h>

// macros for messaging loop
#define CLEAR_BUFFERS() memset(&buffer, 0, 1024); memset(&response, 0, 1024)
#define _READ() ret = socket_read(client, &buffer[0], 1024);    \
                if(ret == -1) {                                 \
                    running = 0;                                \
                    continue;                                   \
                } // if -1
#define _WRITE(msg) ret = socket_send(client, &response[0], 1024);  \
                    if(ret == -1) {                                 \
                        running = 0;                                \
                        continue;                                   \
                    } // if -1                                      \
                    printf("Message sent: %s\n", response);

#define GET_ACTION(action_ptr)         _READ(); *action_ptr = atoi(buffer);    _WRITE("OK"); CLEAR_BUFFERS()
#define GET_LONG_POINTER(data_ptrr)     _READ(); *data_ptrr = (unsigned long*) strtoul(buffer, NULL, 0); _WRITE("OK"); CLEAR_BUFFERS()


// no usage, tells me if shit is happening in a thread or not
#define _thread

// message handler function pointer, comes from the main lib
handle_message_ptr handle_msg;

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
        CLEAR_BUFFERS(); 

        int action;
        unsigned long* data_ptr;

        printf("Getting action\n");
        GET_ACTION(&action);
        printf("Getting pointer\n");
        GET_LONG_POINTER(&data_ptr);
        printf("action : %d, pointer: %lX ,message read: %s\n",action, (unsigned long*) data_ptr, &buffer[0]);


        printf("Waiting for msg\n");
        _READ();
        if(ret != 0) {
            handle_msg(data_ptr, &buffer[0], &response[0], action);
        }
        _WRITE(response);
        // oh, so clean
    }
    
    printf("Got out of the main loop\n");

    socket_free(client);

    return NULL;
}


/*
while(running) {
        // clear buffers from any data
        memset(&buffer, 0, 1024);
        memset(&response, 0, 1024);

        
        ret = socket_read(client, &buffer[0], 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        printf("Got something from socket_read\n");
        if(ret != 0) {
            char action = buffer[0];        // take the first byte from the data
            printf("Progressing\n");
            unsigned long* data_ptr = (unsigned long*) &buffer[1];    // take the data_ptr (8 bytes)
            printf("action : %d, pointer: %lf ,message read: %s\n",action, data_ptr, &buffer[8]);

            handle_msg(data_ptr, &buffer[9], &response[0], &action);
        }
        
        ret = socket_send(client, &response[0], 1024);
        if(ret == -1) {
            running = 0;  
            continue;
        } // if -1
        printf("Message sent: %s\n", response);
        
    }
*/
EXPORT_FUNCTION void networking_set_message_handler(handle_message_ptr msg_handler) {
    handle_msg = msg_handler;
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
