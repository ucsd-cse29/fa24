# Header Files and more string functions

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
It's not necessary to fully understand the implementation of `start_server`, but the idea behind the function is available in the pa3 [writeup](https://github.com/ucsd-cse29/fa24/blob/main/src/pa/pa3/http-server.md).

The functions declared in the header will be defined in its corresponding `.c` file (`http-server.c` in this case). 
Every function in a C file must have his visibility defined in one of two ways:
- Public functions should be defined in the header file. These are the functions that will be accessed by any external source files.
- Private functions (typically helpers or utilities) **must** include the `static` keyword in its declaration (in the source file) to specify its internal use only.

When compiling our program, all source files must be included as arguments to `gcc`.

**Task**: Try compiling the `numeric_server` using gcc. Create a `Makefile` with your new compilation command. (HINT: Remember how we did that in the [last lab](../week4/c-multifile-make.html)?)

**In your notes:** Write down what happens when you don't include the `http-server` file in `gcc`.  What happens when you **ONLY** include the `http-server file` in `gcc`? 

After getting the server running, open your browser and go to `localhost:<port>` where port is the number defined in the terminal.

**In your notes:** Add a screenshot of what you see.

Congrats, we got a working server running!

## String functions

For the purposes of this lab, we'll also need a few more functions from the C `<string>` library in order to build our backend.

**In your notes**: For each of the following functions, add its signature and a brief description of what the function does.

* `strstr`

* `sscanf`

* `strncat`

* `strncmp`