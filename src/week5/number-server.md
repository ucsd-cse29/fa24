# Part 3: Implementing the Number Server

Now that we've completed our walkthrough of the basics of the http-server library. It's time to use the library to create our own server. 

The number-server needs handle 3 different routes:


- `/shownum`

    This function responds to the client socket with the current value of `num`.

- `/increment`

    This function increments the value of `num` by one and responds to the client with the new value of `num`.

- `/add?value=NNN`

    This function increments the value of `num` by the value encoded in `NNN` (a decimal integer) and responds to the client with the new value of `num`

We'll walk you through the first one, then you can try the others on your own.

## 3.1 `/shownum`

1. Every HTTP response first begins with headers, which include a **status code**. Every response to a successful request begins with:
    ```
    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
    ```
The status code of 200 tells the client that the incoming response is valid. 

2. We define a `char[]` to hold the HTTP response to send. In `http-server.h`, we define `BUFFER_SIZE` as 2048, which we can use as the size of our response buffer.

3. Next, we encode the message to return back to the client. For `handle_shownum()` the current value of `global_num` should be encoded into the response message. Which C string function can we use to do this? (**Hint:** see the previous section of the lab)

4. After completing the logic for the route, we need to ensure that this code is only called on the correct url. In `handle_response`, the `url` only includes the path from `/` to the end. If we only want `handle_shownum()` to run when `/shownum` exists as a *substring* in the `url`. What C string function can we use to do this?

After completing the `/shownum` route, curl the route with:

```
curl localhost:<port>/shownum
```

We should see 
```
Your number is 0
```
We officially got a web server running! Now, you have all the tools to implement the other functions of `number-server`.

## 3.2 Query paramters:



## 3.3 `/add?value=NNN`


**WIP: TODO:start with what they need to accomplish, that motivates the explanation** For the /add endpoint, we'll need to specify some additional info (the number to add)

When sending a GET request in HTTP, the only data sent from the client to the server is the URL. This means that any data we need to include with the request must be encoded into the url.
This data is encoded as **query parameters** which follow a `?` in the url and usually take the form of
```
?keyA=value&keyB=value&...
```
<!-- To parse the query string to extract the necessary values, we'll use a new C function:
```c
int sscanf(char* str, char* format, ...)`.
```

`sscanf()` is somewhat of a combination of the `fgets()` and `printf()` that we've previously used before. It reads formatted input (`format`) from a string `str` and stores the result at the provided addresses.
In the case of `handle_add`, we can extract the query parameter from the URL like so:
```c
int add_val;
sscanf(query, "value=%d", &add_val); 
```
** WIP TODO: we don't have a `query` in our starter, make this take path?**

In this example, the query string is passed in, and the value of the query parameter is copied into the address of our variable `add_val`. -->
