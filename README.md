# Proiect OM

## NOTICE
This program is free, and will be free, commercial use is not allowed. 
I have dropped development on this tool.

## MAIN PROGRAM
Main programs starts in src/console_interface.c:  
  ```C
  EXTERNAL_FUNCTION void start_console_app() {
    ...
    console_main();
  }
  
  static void console_main() {
    ...
  }
  ```
  
## Program structure

- serverapp: contains the networking implementation, had it out in a separate project because O.S. dependencies (pthreads, networking), specifically linux
- socketapp: to debug serverapp

 These 2 above will be deleted soon, will only compile on linux, and have no use, because I dropped the networking interface implementation in favour for a process-based one
- testapp: it's called testapp because I wanted to only use the library, loading it and using it's functions. Testapp was a program that loaded the library and did things, to debug/make sure it's working correctly, now it's job is to load the library and execute it, being the program's main loader.
- src: contains the source code for the program

  
## HOW TO INSTALL & USE
uhm, long explanation, probably another time. Time for a short one...

You can't just import this in visual studio or some other IDE, you'll get errors.

=> You'll need CMake, on linux if you have CMake installed you can use

```bash
  sh build.sh
  sh run.sh
```
to start the compilation.

On windows, you have to download CMake tool, source is the CMakeLists.txt directory, and build is the "build" directory
