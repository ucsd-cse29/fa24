# Part 2: HTTP Server

## 2.0 Getting started
#### Task

1. If you haven't done so already, log onto `ieng6`, then run the corresponding prep command for your class (`cs29fa24` for Joe's, `cs29fa24b` for Aaron's).
2. Fork the [lab5 starter repo](https://github.com/ucsd-cse29/lab5-starter), then clone it. (If you're unsure how, you can refer back to how we did this in
   [Lab 3](../week3/index.html#42---git-cli-commands) and [Lab 4](../week4/push-pa2-code.html#pushing-pa2-code-to-github-from-ieng6))

### Header files

Looking into the `lab5` repository, you'll find two **source files** (`number-server.c`, `http-server.c`), and one **header file** (`http-server.h`). 
In the previous labs and PAs for the class, our code has consisted of a single `.c` file, containing a `main()` and all associated functions.
As programs get more complex, it becomes increasingly important to organize the code by seperating it into multiple files.

`http-server.h` should look like this:
```c
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdlib.h>
// ... more #includes

void start_server(void(*handler)(char*, int), int port);
#define BUFFER_SIZE 2048

#endif
```

This header file contains the **declaration** of `start_server`, which includes all info needed for C to call a function, which are its arguments and return type. However the **definition** of the function 
(i.e. the actual code that it runs) are in `http-server.c`.
To call this function, `number-server.c` needs the declaration, which it gets by including `http-server.h`.

> EXTRA INFO 📝: 
> 
> - It's not necessary to fully understand the implementation of `start_server`, but the idea behind the function is available in the pa3 [writeup](https://github.com/ucsd-cse29/fa24/blob/main/src/pa/pa3/http-server.md).
> - Every function in a C file should have its visibility defined in one of two ways:
>     - Public functions (meant to be called from other source files) need to be declared in a header file.
>     - Private functions (typically helpers or utilities) **should always** be declared as `static` (e.g, `static int foo() {...}`) to specify that they shouldn't be visible to other `.c` files.
>
> - The `ifndef/define/endif` at the start and end of a header are an [include guard](https://en.wikipedia.org/wiki/Include_guard)

## 2.1 Compiling with multiple files

When compiling a program with multiple source files, all source (`.c`) files must be included as arguments to `gcc`. NOTE: you don't need to specify the header files to gcc; they are automatically
pulled in by `#include` statements.

#### Task

3. Try compiling the `number_server` using gcc. (Note: you may need to pass in the `-std=c11` flag)
4. **In your notes:** Write down what happens when you don't include the `http-server.c` file in `gcc`.  What happens when you **ONLY** include the `http-server.c` file in `gcc`? 
5. Once you're successfully able to compile this program, create a `Makefile` so that you can compile `number_server` just by typing `make`.
    - (Note: You can refer to how we did this in the [last lab](../week4/c-multifile-make.html#makefiles))
    - You may find it useful to also include the debugging flags from last lab: `-Wall -Wno-unused-variable -fsanitize=address -g`
6. Run the `number-server` you just compiled; it should say something like "Server started on port PPPPP".
7. Open your browser and go to `localhost:PPPPP` where PPPPP is the port number from your server. Your browser will show an error page, but you should see some output from `number-server` in your terminal 
8. **In your notes:** Add a screenshot of the terminal output from `number-server`

Congrats, you've got a working server running!

## 2.2 WIP: STRING HUNT

### String functions

For the purposes of this lab, we'll also need a few more functions from the C `<string>` library in order to build our backend.

**In your notes**: For each of the following functions, look it up in the manpages (`man XXX`), add its signature and a brief description of what the function does.

* `strstr`

* `sscanf`

* `snprintf`


## 2.3 HTTP 404 Response


When we want to view a given **url** e.g. "http://ieng6-201.ucsd.edu:8000/post?user=joe&message=hi", a client (a browser, curl, or our fancy-client) sends an **HTTP request**. 
When we want to view a given **url** e.g. "http://ieng6-201.ucsd.edu:8000/post?user=joe&message=hi", a client (a browser, curl, or our fancy-client) sends an **HTTP request**. 
Everything 
When we want to view a given **url** e.g. "http://ieng6-201.ucsd.edu:8000/post?user=joe&message=hi", a client (a browser, curl, or our fancy-client) sends an **HTTP request**.  
Everything 
The request is the client asking the server to do something. The server takes the request, completes it (if possible) and returns a **response** to the client.

An HTTP request looks something like this:
```
GET /some/url/path?params=foo HTTP/1.1
Host: localhost:37107
... many other headers
```

> NOTE 📝: There's a lot of names that refer to parts of this `HTTP target`.
> It's not a url, as url refers to the full address, e.g. `http://address:port/path/to/page?query`.
> It's also not just the path, as technically the path goes only up to the first '?', and anything after that is the "query-string"
> The path would also sometimes be called an "endpoint" in the context of web-APIs or web-servers.

Right now, we can compile and run our numeric-server, but it doesn't serve anything because the functions have not yet been implemented.
#### **Task**
1. Use `curl` to access `localhost:<port>` with the numeric server running. How does `curl` respond?
2. **In your notes**: Add a screenshot of your browser accessing `localhost:<port>` with the numeric-server still running. How is this different than if the server was not running?



In the next part of this lab, you will make your server handle three additional **endpoints**. For now, we can serve a 'Not Found' response to the client for all our unimplemented functions.

To send this message across the network, we use the `write` function:
```c
ssize_t write(int fd, const void buf[count], size_t count)
```
The `write` function is used to write `count` bytes of `buf` to the `fd` file descriptor. In this case, writing our message to the `client_sock` fd will send the text to our client through its socket.

To send the 'Not Found' response, we first need to respond with an HTTP header (this tells the client what kind of response with this)
```
// Define this at the top of your C file:
const char HTTP_RESP_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n"
//...
// Once you've gotten a request:
write(client_sock, HTTP_404_NOT_FOUND, strlen(HTTP_404_NOT_FOUND))
```

404 is a **status code** that tells the client that the URL request was not found. Optionally, we can include any other text we want to display on the client.

#### **Task**
3. Once you've done this, connect to your server from a browser and make sure you can see the error message, including the path of the url you connected to.
4. **In your notes:** Add a screenshot of the 'Not Found' page in your browser. How is this different from the previous error page?
5. Try connecting to different paths on your server. Does you notice anything interesting if you put in add special characters to the path? Spaces? Emoji?
 


