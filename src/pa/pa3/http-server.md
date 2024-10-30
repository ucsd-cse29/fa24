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
    write(client_socket, HTTP_200_OK, strlen(HTTP_200_OK));
    write(client_socket, "Hello!", 6);
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
Hello!
$ curl "http://localhost:PPPPP/post?user=aaron&message=sup"
Hello!
```

Then, every time the server gets a request, it will call the `handle_request`
function, which will print the contents of the request, and then use the `write` system call to send a response back to the client (in this case with a constant string). This is the entry point to our program, and it's a good starting point for you to build up from!

One other tip for using `start_server`:

- If `port` is 0, the library will pick an open port provided by the operating
system. This is convenient for getting started
- However, when you restart a program it's annoying to have to change the port
number in any requests you have in your bash history, etc. So you can also
provide the port number as an argument, which could be hardcoded or taken from a
command-line argument. You can do that to re-run the program with the same port
it used last time to keep your examples consistent

## HTTP Requests

The first argument to `handler` is a `char*` with a a reference to the HTTP
request. For our `chat-server`, all requests will be `GET` requests and will
look something like

```
GET /post?user=joe&message=hi HTTP/1.1
Host: localhost:36611 User-Agent:
curl/7.68.0 Accept: */ *
```

The string after `GET` is the path of the request, and that's the part that will
change depending on the type of request we get. Part of the job of the
`chat-server` will be to extract the relevant information from the path, like
which action to take (post, react, etc.) and the parameters of the action (user,
message, etc.) in order to work with them.

It probably makes sense to use some C string library functions to do this. In
particular `strtok` will allow you to “split up” a string by replacing
delimiters like ` `, `&`, and `=` with null terminators. You may also find
`strcspn`, `strstr`, or `strpbrk` useful; it's up to you to come up with a plan
to put these together to extract the information out of each request.

## HTTP Responses

The second argument to `handler` is an `int` that is a file descriptor for the
response. The `http-server` library has set things up so writing to the socket
sends bytes directly back to whatever client made the request.

The format of a HTTP response for a successful response is

```
HTTP/1.1 200 OK
Content-Type: text/plain

... response body ...
```

**Note**: A nuance of this is that the newlines in HTTP responses are not just
`\n`; [they are required to be
`\r\n`](https://en.wikipedia.org/wiki/HTTP_message_body) (which, interestingly,
is how line endings
work on Windows). Some software will work with just a `\n` for line breaks, but
the correct thing to do is use `\r\n`, so in a string literal the HTTP header above
would look like

```
"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n...response body...
```

There are many other `Content-Type`s in the world other than `text/plain`! But
we will focus on just plain text reponses for this assignment.
