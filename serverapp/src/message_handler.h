#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_
#include "networking/networking_interface.h"
#include "structs.h"

/*  I wanted to this part of the implementation hidden in the main library.
   But I had to use threads and didn't want to bloat the code, threads here, threads there...  */

// Handle web requests
//INTERNAL_FUNCTION void handle_message(struct data* data, char* msg, char* response, int* stage);
INTERNAL_FUNCTION void handle_message(struct data* data, char* msg, char* response, int action);

// The message handler requires a DataOps struct to manipulate the data
// Hides the implementation
INTERNAL_FUNCTION void message_handler_set_dataops(struct DataOps*);

// Returns the function pointer to the message handling function.
// It's purpose was to get the function handle from the main lib - hiding the implementation.
EXPORT_FUNCTION void* message_handler_get(); 


#endif