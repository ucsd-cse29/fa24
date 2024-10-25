# Implementation Guide – HTTP Protocol and Working with HTTP Requests

Your `chat-server` will need to read requests and send responses in HTTP.

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