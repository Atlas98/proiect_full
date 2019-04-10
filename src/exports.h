#ifndef _EXPORTS_H_
#define _EXPORTS_H_


#ifdef _WIN32
#define EXPORT_FUNCTION __declspec(dllexport)
#define INTERNAL_FUNCTION 
#elif __linux__
#define EXPORT_FUNCTION extern
#define INTERNAL_FUNCTION __attribute__ ((visibility ("hidden"))) 
#endif

#endif