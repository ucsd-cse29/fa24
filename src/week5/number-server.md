# Implementing the Number Server

Now that we've completed our walkthrough of the basics of the http-server library. It's time to use the library to create our own server. 


- `handle_shownum(int client_sock)`

This function responds to the client socket with the current value of `num`.

- `handle_increment(int client_sock)`

This function increments the value of `num` by one and responds to the client with `Number incremented!`


- `handle_add(char* url, int client_sock)`

This function increments the value of `num` by the `value one and responds to the client with `Number incremented!`

- `handle_response(char* request, int client_sock)`

This function takes in a `char*` of the request URL and an `int` id of the client socket, and directs the response to the corresponding route.


For these functions, try implementing them on your own. Here, we'll implement the `handle_shownum()` function, with the other functions sharing a similar structure.

---
1. We define a `char[]` to hold the HTTP response to send. In `http-server.h`, we define `BUFFER_SIZE` as 2048, which we can use as the size of all of our buffers.

2. Every HTTP response first begins with a **status code**. A status code of 200 means the server successfully completed the request. Let's first copy the `HTTP_200_OK` string to the start of our response.

3. Next, we encode the message to return back to the client. For `handle_shownum()` the message should be `Number: X` where X is the value of our num from the server.

After fully formatting our response, we just need to send it back to the client. For that, we use:
```c
    ssize_t write(int fd, const void buf[count], size_t count)
```

The `write` system call is used to write `count` bytes of `buf` to the `fd` file descriptor. In this case, writing to the `client_sock` fd will send the message to our client through its socket.

### HTTP Query Parameters

When sending a GET request in HTTP, the only data sent from the client to the server is the URL. This means that any data we need to include with the request must be encoded into the url.
This data is encoded as **query parameters** which follow a `?` in the url and usually take the form of
```
?keyA=value&keyB=value&...
```
To parse the query string to extract the necessary values, we'll use a new C function:
```c
int sscanf(char* str, char* format, ...)`.
```

`sscanf()` is somewhat of a combination of the `fgets()` and `printf()` that we've previously used before. It reads formatted input (`format`) from a string `str` and stores the result at the provided addresses.
In the case of `handle_add`, we can extract the query parameter from the URL like so:
```c
int add_val;
sscanf(query, "value=%d", &add_val); 
```

In this example, the query string is passed in, and the value of the query parameter is copied into the address of our variable `add_val`.
