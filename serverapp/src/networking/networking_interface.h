#ifndef _NETWORKING_INTERFACE_H_
#define _NETWORKING_INTERFACE_H_

/* This code belonged to the main library */
#define EXPORT_FUNCTION
#define INTERNAL_FUNCTION

// data_ptr, msg_ptr, response_ptr, action int - message handler params
// data_ptr is an unsigned long, and it is the memory location of a session's data struct
typedef void (*handle_message_ptr)(void*, void*, void*, int);

EXPORT_FUNCTION void start_networking_interface();
EXPORT_FUNCTION void networking_set_message_handler(handle_message_ptr msg_handler);


#endif