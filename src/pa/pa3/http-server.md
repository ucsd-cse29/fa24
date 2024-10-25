# Implementation Guide: The `http-server` Library

We've provided you with `http-server.c` and `http-server.h`. This is code for
you to treat as a _library_, you shouldn't change it at all (though you may
learn from reading it!).

It provides one function for you to use:

```
void start_server(void(*handler)(char*, int), int port);
```

This function takes two arguments: a `handler` that takes HTTP requests and
writes responses, and a `port` for telling the server what address to use. The
`port` can be `0` to ask the operating system to choose one for us.

The type for `handler` is the type of a _function pointer_, which is the address
of a function. To use `start_server`, we define a function (it can have any
name) with the appropriate signature and pass it into `start_server` as an
argument. The `handler` function takes two arguments:

```
void(*handler)(char*, int)
```

- The first, the `char*`, is a string containing the request from the internet.
It will be an HTTP request.
- The second, the `int`, is a _file descriptor_ that our program can use to
write a response using the `write` system call

Here's a straightforward example that just responds to the user with a constant string:

```
#include "http-server.h" // http-server includes a lot of other useful things
char const* HTTP_200_OK = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
void handle_response(char *request, int client_socket) {
    printf("The user sent a request with: %s\n", request);
}
int main() {
    start_server(&handle_response, 0);
}
```

```
$ gcc -o print-request print-request.c http-server.c
$ ./print-request
Server started on port PPPPP (will be a specific number for you)
# the lines below print *when the request is received*
The user sent a request with: GET /post?user=joe&message=hi HTTP/1.1
Host: localhost:36611
User-Agent: curl/7.68.0
Accept: */*
The user sent a request with: GET /post?user=aaron&message=sup HTTP/1.1
Host: localhost:36611
User-Agent: curl/7.68.0
Accept: */*
```

(in another terminal)

```
$ curl "http://localhost:PPPPP/post?user=joe&message=hi"
curl: (52) empty reply from server
$ curl "http://localhost:PPPPP/post?user=aaron&message=sup"
curl: (52) empty reply from server
```

Then, every time the server gets a request, it will call the `handle_request`
function, which will print the contents of the request. This simple version
won't send a response to the client that made the request (like `curl` or a web
browser, hence the `curl` error mesage)! But it shows how the `handle_request`
function is called repeatedly on each request.

The section on HTTP [FILL link] shows how requests and responses should be
formatted for the HTTP protocol.

One other tip for using `start_server`:

- If `port` is 0, the library will pick an open port provided by the operating
system. This is convenient for getting started
- However, when you restart a program it's annoying to have to change the port
number in any requests you have in your bash history, etc. So you can also
provide the port number as an argument, which could be hardcoded or taken from a
command-line argument. You can do that to re-run the program with the same port
it used last time to keep your examples consistent