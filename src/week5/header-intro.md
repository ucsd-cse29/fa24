# Header Files and more string functions

In the previous labs and PAs for the class, we've been localizing our source code into one C file, which includes the  `main()` function, as well as any other helper functions needed to properly execute the `main`.
As programs get more complex and size of the codebase grows, it becomes more important to organize the code by seperating it into multiple files. In C, this is achieved through **header files**

Before we begin, first clone the lab5 starter repo from [here](https://github.com/ucsd-cse29/lab5-starter).

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

### String functions

For the purposes of this lab, we'll also need a few more functions from the C `<string>` library in order to build our backend.

**In your notes**: For each of the following functions, add its signature and a brief description of what the function does.

* `strstr`

* `sscanf`

* `strncat`

* `strncmp`

## 



The way our server works, a client (a browser, curl, or our fancy-client) sends a **request** to our server. The request is the client asking the server to do something. The server takes the request, completes it (if possible) and returns a **response** to the client.

Right now, we can compile and run our numeric-server, but it doesn't serve anything because the functions have not yet been implemented. 

As a placeholder, we can serve a 'Not Found' response to the client for all our unimplemented functions.

To send this message across the network, we use the `write` system call:
```c
ssize_t write(int fd, const void buf[count], size_t count)
```
The `write` system call is used to write `count` bytes of `buf` to the `fd` file descriptor. In this case, writing our message to the `client_sock` fd will send the text to our client through its socket.

To send the 'Not Found' response, we write the following:
```
"HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
```

404 is a **status code** that tells the client that the URL request was not found. 

If done correct, compiling and running `numeric-server` should change the browser page to a "Page cannot be found"