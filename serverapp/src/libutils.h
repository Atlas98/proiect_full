#ifndef LIB_UTILS_H_
#define LIB_UTILS_H_

typedef void* lib_handle;
typedef void* function_handle;

lib_handle load_library(char* file_name);
function_handle load_function(lib_handle, char* function_name);


#endif