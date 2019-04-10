# Proiect OM

Some things are not always correct, this program's decision making ability reflects mine, your average computer program can't correctly guess the best option without some knowledge about the subject. So... In order for this program to work properly I need that knowledge.

## NOTICE
This program is free, and will be free, code-wise it is not in the best shape, I need to:
  - delete a lot of garbage code I no longer need
  - comment some things
  - implement a better interface: I had to rewrite a lot of code, because at first my plan was to load the library in php's codespace and call it's functions but it's a lot more complex. Then, I implemented some networking code to talk to the webserver, but it was complex and it would've took a lot of time. Now, creating a process via proc_open was cleaner and more stable than the networking solution, but it lacks things.

## Program structure

- serverapp: contains the networking implementation, had it out in a separate project because O.S. dependencies (pthreads, networking), specifically linux
- socketapp: to debug serverapp

 These 2 above will be deleted soon, will only compile on linux, and have no use, because I dropped the networking interface implementation in favour for a process-based one
- testapp: it's called testapp because I wanted to only use the library, loading it and using it's functions. Testapp was a program that loaded the library and did things, to debug/make sure it's working correctly, now it's job is to load the library and execute it, being the program's main loader.
- src: contains the source code for the program
  
## TODO list: 
  - fix some things
  - finish chapter 5
  - finish chapter 6
  - Autocad drawing generator (get an autocad script that you can execute, generating your drawing)
 
 ## About fixing some things:
  - Tabel A7.1, Dr above 85 = not implemented (will add it soon, a lot of typing q_q)
  - Various lengths and diameters in chapter 3(Dr, Dperii, Lperii, etc) are not 100% truly correct, I don't know how you get to choose them
  
  and such... there are some tricky bits, no clear instructions or clues on how to deal with them,
  it gets more complex + the final drawing got a stupid deadline + after all this, you'll forget everything you've done
  # And this is the why, many people offer themselves to do this for you, for money, because they already know... you don't, and you're not interested in knowing.
