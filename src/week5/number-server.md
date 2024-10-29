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

4. After completing the logic for the route, we need to ensure that this code is only called on the correct url. In `handle_response`, the `url` only includes the path from `/` to the end. If we only want `handle_shownum()` to run when `/shownum` exists as a *substring* in the `url`, what C string function can we use to do this?

After completing the `/shownum` route, curl the route with:

```
curl localhost:<port>/shownum
```

We should see 
```
Your number is 0
```
We officially got a web server running! Now, you have all the tools to implement the other functions of `number-server`.

## 3.2 Query parameters:


When sending a GET request in HTTP, the only data sent from the client to the server is the URL. This means that any data we need to include with the request must be encoded into the url. 

This data is encoded as **query parameters** which follow a `?` in the url and usually take the form of
```
?keyA=value&keyB=value&...
```
The server can then extract the values it needs from this query string and use it in its execution.


For the case of the `/add` endpoint, we need to extract the addition operand from the url. A valid request to `/add` must have the path of
```
/add?value=<number>
```
Because this endpoint only takes in one argument, parsing is simple.


**Task**:

1. What string function could we use to *scan* through our path and extract the number?
2. Try using this function to print out the value of `value` from the url path
3. Implement the `/add` endpoint for your numeric-server
4. **In your notes:** Show your numeric-server working functionally
5. **In your notes:** Write what you think might cause our numeric-server to crash?