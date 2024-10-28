

In the previous labs and PAs for the class, we've been localizing our source code into one C file, which includes the  `main()` function, as well as any other helper functions needed to properly execute the `main`.
As programs get more complex and size of the codebase grows, it becomes more important to organize the code by seperating it into multiple files. In C, this is achieved through **header files**

## Header files

Looking into the `lab5` repository, you'll find two files: `http-server.c` and `http-server.h`. The `.c` file extension is the source code file that we've been previously accustomed to. The `.h` file is its header file. `http-server.h` should look something like this:
```c
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>


void start_server(void(*handler)(char*, int), int port);

#define BUFFER_SIZE 2048

#endif
```
Similar to an interface in Java, the header contains function signatures and other definitions that can be shared across multiple C files. In this instance, we only define the `start_server()` function, which we will use later in the lab to start our chatroom server.
The functions declared in the header will be defined in its corresponding `.c` file (`http-server.c` in this case). 
<!--Every function in a C file must have his visibility defined in one of two ways:
- Public functions **must** be defined in the header file. These are the functions that will be accessed by a 
Every public function  Private functions (typically helpers or utilities) **must** include the `static` keyword in its declaration (in the source file) to specify its visibility. -->

Any function **not** declared in the `.h` file cannot be accessed by other source files. As you continue to work on your PA, you can (and should) add the function declarations for the other functions you implement to this file.