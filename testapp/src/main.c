#include <stdio.h>
#include <stdlib.h> 

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#include <unistd.h>
#include <dirent.h>
#endif

typedef void(*start_console_app_ptr)(void);

int main() {
	setbuf(stdout, NULL);

	printf("Loading Application...\n");
	#ifdef _WIN32
    void* libHandle = LoadLibrary("AtlasOM.dll");
	if (libHandle == NULL) printf("Lib handle is null!\n");
    start_console_app_ptr funcHandle = (start_console_app_ptr) GetProcAddress(libHandle, "start_console_app");
	if (funcHandle == NULL)
		printf("Func handle is null!\n");

	#elif __linux__
	/*char cwd[255];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		fprintf(stderr, "Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}	*/

	void* libHandle = dlopen("./libAtlasOM.so", RTLD_GLOBAL | RTLD_NOW);
	if (libHandle == NULL) {
		printf("Lib handle is null!\n");
		fprintf(stderr, "dlopen failed: %s\n", dlerror()); 
      	exit(EXIT_FAILURE); 
	}
 
    start_console_app_ptr funcHandle = (start_console_app_ptr) dlsym(libHandle, "start_console_app");
	if (funcHandle == NULL)
		printf("Func handle is null!\n");
	#endif

	funcHandle();
	printf("Finished\n");
    return 0;
}