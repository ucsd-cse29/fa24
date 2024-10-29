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

## 3.1 Getting started

#### Successful Responses

However, now that we're adding support for `/shownum` and friends, we need to be able to send back a successful response,
not just a "page not found". The HTTP status code for success is 200, so a successful response would look something like this:

```
HTTP/1.1 200 OK
Content-Type: text/plain

... body of response ...
```

As a string literal, the response header would look like this:
```
"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
```

#### Path parsing:

We also need to ensure that our `/shownum`, `/increment`, and `/add` responses only trigger when the correct path is requested, a path like `/badpath` should still result in a 404 response.
Using a function like `strcmp` or `strstr` can be useful to check if the path matches a given string.

#### Maintaining state

In the lab5 starter, `num` is a global int variable, so functions can read/write its value.

----

After completing the `/shownum` route, curl the route with:

```
curl localhost:<port>/shownum
```

You should see something like: 
```
Your number is 0
```
Congrats! You officially got a web server running! Now, you have all the tools to implement the other functions of `number-server`.

## 3.2 Query parameters:

This section might be useful once you start working on the `/add` endpoint.

When sending a GET request in HTTP, any data accompanying the request needs to be sent as part of the path. This data is encoded as **query parameters** which follow a `?` in the path and usually take the form of
```
?keyA=foo&keyB=bar&...
```

For the case of the `/add` endpoint, we need to encode the amount to add as part of the query string. A valid request to `/add` looks like
```
/add?value=<number>
```
Parsing query parameters correctly can be tricky, but in this case we only have one parameter to worry about, which makes it easier.


**Task**:
1. What string function could we use to *scan* through our path and extract the number?
2. Try using this function to print out the number after `value=` from the url path
3. Implement the `/add` endpoint for your number-server
4. **In your notes:** Put a screenshot of your number-server working with the endpoints you implemented.
5. **In your notes:** Think of a request you could make that would cause your numeric-server to crash.
