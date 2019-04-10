#include "libutils.h"
#include <stdlib.h>

#ifdef __linux__
#include <dlfcn.h>

#elif __WIN32
#include <Windows.h>
#endif

lib_handle load_library(char* file_name) {
    lib_handle handle = NULL;
    #ifdef __linux__
    handle = dlopen(file_name, RTLD_NOW | RTLD_GLOBAL);
    #endif

    return handle;
}

function_handle load_function(lib_handle lib, char* function_name) {
    function_handle handle = NULL;
    #ifdef __linux__
    handle = dlsym(lib, function_name);
    #endif

    return handle;
}
