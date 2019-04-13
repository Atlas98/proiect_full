# Proiect OM

## NOTICE
This program is free, and will be free, commercial use is not allowed. 

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
  Code-wise it is not in the best shape, I need to:
  - <del>delete a lot of garbage code I no longer need</del>
  - comment some things
  - implement a better interface: I had to rewrite a lot of code, because at first my plan was to load the library in php's codespace and call it's functions but it's a lot more complex. Then, I implemented some networking code to talk to the webserver, but it was complex and it would've took a lot of time. Now, creating a process via proc_open was cleaner and more stable than the networking solution, but it lacks things.
  
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

  
## CONTRIBUTING
  If something is not right, please contact me to get to the root of the problem, I aim to make this as perfect as possible.
  
  Computer programs calculate with higher precision, so a small error is to be expected
  
  ex: 3.14159265359 * 29.9 = 93.9336203423
  
  but 3.14 * 29.9 = 93.886
  
  
## TODO: 
  - fix some things
  - finish chapter 5
  - finish chapter 6
  - Autocad drawing generator (get an autocad script that you can execute, generating your drawing)
 
 ## About fixing some things:
  - Tabel A7.1, Dr above 85 = not implemented (will add it soon, a lot of typing q_q)
  - Various lengths and diameters in chapter 3(Dr, Dperii, Lperii, etc) are not 100% truly correct, I don't know how you get to choose them
  
  and such... there are some tricky bits, no clear instructions or clues on how to deal with them,
  it gets more complex + the final drawing got a stupid deadline + after all this, you'll forget everything you've done
