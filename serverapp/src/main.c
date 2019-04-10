#include "structs.h"
#include "networking/networking_interface.h"
#include "libutils.h"
#include "message_handler.h"

#include <stdlib.h>
#include <stdio.h>



int main() {
    // Open up
    lib_handle lib = load_library("./libAtlasOM.so");
    if(lib == 0) {
        printf("Library handle is null, are you sure you have the main library?\n");
        return -1;
    }

    function_handle func = load_function(lib, "get_data_ops");
    if(func == 0) {
        printf("Function handle is null, maybe it is not implemented within the main library?\n");
        return -1;
    }
    get_data_ops get_ops_func = (get_data_ops) func;

    message_handler_set_dataops(get_ops_func());
    networking_set_message_handler(message_handler_get());
    start_networking_interface();

    printf("Program finished\n");
    return 0;
}