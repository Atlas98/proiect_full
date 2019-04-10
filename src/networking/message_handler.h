#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_
#include "networking_interface.h"
#include "../structs.h"

INTERNAL_FUNCTION void handle_message(struct data* data, char* msg, char* response, int* stage);
INTERNAL_FUNCTION void message_handler_set_dataops(struct DataOps*);

// returns the function pointer to the message handling function
EXPORT_FUNCTION void* message_handler_get(); 


#endif