# PA3 - Web Server

- **Due 10:10pm Monday, November 11, 2024**
- Github Classroom Assignment: [https://classroom.github.com/a/hlq9KJbK](https://classroom.github.com/a/hlq9KJbK)

<!--
## Resubmission instructions
**If you want to resubmit PA3, please read this section carefully. You need to pass all the tests in the original PA3, while also implementing an extra functionality and answering a new design question described below.**

In addition to `/chats`, `/post`, `/react`, `/reset` requests, the chat server also listens for the following request:
### `/edit`

```
`/edit?id=<id>&message=<message>`
```

Edits the message in the post with the given id (the ids are the `#N` at the
beginning of posts) by replacing it with the new message. It must
respond with the list of all chats (including the new one).


Limits and constraints:

- If the id is not the ID of some existing chat, respond with some kind of error
(HTTP code 400 or 500)
- If a parameter ( `id` or `message`) is missing, respond with some kind of
error (HTTP code 400 or 500)
- If message is longer than 255 bytes, respond with some kind of error (HTTP
code 400 or 500)

## Updated DESIGN questions for the resubmission

1. We recommended representing chats and reactions as structs. Another option would be to just represent every chat as the string of text that gets printed – a single `char*` per chat. Then the list of all chats would be a `char**`. Adding a reaction would just append a new reaction to the string for that chat. What is one good and one bad thing about this alternate design? For this part, consider only the original implementation without `/edit`.

2. How would this `char**` design make it harder to add the `/edit` feature?
-->

## Web Servers and HTTP

[HTTP](https://en.wikipedia.org/wiki/HTTP) is one of the most common protocols
for communicating across computers. At the systems programming level, this means
using _system calls_ (usually in C) to tell the operating system to send bytes
over a network.

One nice feature of HTTP is that it is a primarily text-based protocol, which
makes it more straightforward for humans to read and debug. It is also well-understood by web
browsers and programs like `curl`, making it easy to test and connect to
user-facing devices.

It's useful to get experience with the format of HTTP, and with using system
calls in C to manipulate HTTP requests.

## Task – Chat Server

In this programming assignment, you'll write a C program to implement a _chat
room_ (think a plain-text version of [Slack](https://slack.com/) or
[Discord](https://discord.com/)).

It's best to complete the PA on `ieng6`, because it gives a consistent testing
environment for the live server.

You can also use the client from [Lab 5](https://ucsd-cse29.github.io/fa24/week5/start-pa3.html) to try out your server.

Your programs should compile and run with:

```
$ make chat-server
$ ./chat-server <optional port number>
```

The server should start with `./chat-server` and print a single message:

```
$./chat-server
Server started on port PPPPP
```

If a port number was provided, it should use that port, otherwise it should
print an open port that was selected.

It should continue running, listening for requests on that port, until shutdown
with Ctrl-c. It can print any other logging messages or other output needed to
the terminal.

The requests the chat server listens for are described in this section

### `/chats`

A request to `/chats` responds with the plain text rendering of all the chats.

The rendered chat format is

```
[#N 20XX-MM-DD HH:MM]   <username>: <message>
                    (<rusername>)  <reaction>
                        ... [more reactions] ...
... [more chats] ...
```

Where:

- `#N` is `#` followed by a number like `#5` or `#33`, where the integer is the id of the
chat (ids start at 1 and count up).
- `YYYY-mm-dd HH:MM` is the _timestamp_ of the chat (when it was sent).
    - `YYYY` is the year, like `2024`
    - `mm` is the two-digit month, like `10` for October
    - `dd` is the two-digit day, like `31`
    - `HH` is the two-digit hour in 24-hour format, like `14` for 2pm
    - `MM` is the two-digit minute, like `55`
- `<username>` is the username of the user who sent the chat
- `<message>` is the text of the message the user entered
- `<rusername>` is the name of a user who reacted to the message
- `<reaction>` is a _reaction_ to a message

In terms of alignment and spacing:

- There should be at least one space between the number and the timestamp
- There should be at least one space between the closing `]` and the username
- There should be _no_ space right after the username in a chat, it should be
immediately followed by a colon
- There should be a single space after the colon before the message
- There should be some space before the `(` in a reaction, no space between the
`()` and the username, and some space after the `)` before the reaction message

You can put in whatever effort you like into lining things up nicely within
these constraints, but these are the requirements.

So an example chats rendering might look like:

```
[#1 2024-10-06 09:01]         joe: hi aaron
[#2 2024-10-06 09:02]       aaron: sup
[#3 2024-10-06 09:04]         joe: working on the example chat for the PA
[#4 2024-10-06 09:06]       aaron: oh cool what should it say
[#5 2024-10-06 09:07]         joe: I dunno we could go pretty meta with it? I pushed an example go check it out. like a chat about the chat
[#6 2024-10-06 09:10]       aaron: eh kinda lame tbh
[#7 2024-10-06 09:11]         joe: whatever I already wrote it, going with it as-is
[#8 2024-10-06 09:12]       aaron: ok but make sure we don't look like jerks
[#9 2024-10-06 09:12]       aaron: or at least not me
                            (joe)  👍🏻 
[#10 2024-10-06 09:12]         joe: good talk
```


Here's another:

```
[#1 2024-10-24 13:01]        yash: hi all! react with 👍🏻 if you think the lab is good to go, or 😬 if you think it needs more testing
                          (aaron)  👍🏻 
                          (elena)  😬 
                         (arunan)  😬 
                          (janet)  😬 
                         (travis)  😬 
                            (joe)  🐿️
[#2 2024-10-24 13:02]        yash: OK we'll go with what joe said
```

### `/post`

A `post` request looks like this:

`/post?user=<username>&message=<message>`

This creates a new chat with the given username and message string with a
timestamp given by the time the request is received by the server.  It must
respond with the list of all chats (including the new one).

Limits and constraints:

- If a parameter (`username` or `message`) is missing, respond with some kind of
error (HTTP code 400 or 500)
- If username is longer than 15 bytes, respond with some kind of error (HTTP
code 400 or 500)
- If message is longer than 255 bytes, respond with some kind of error (HTTP
code 400 or 500)
- If a post would make there be more than 100000 (one hundred thousand) chats,
the server should respond with an error (HTTP code 404 or 500)

### `/react`

```
/react?user=<username>&message=<reaction>&id=<id>
```

Creates a new *reaction* to a chat by the given username with the given message
string, reacting to the post with the given id (the ids are the `#N` at the
beginning of posts). It must
respond with the list of all chats (including the new one).


Limits and constraints:

- If the id is not the ID of some existing chat, respond with some kind of error
(HTTP code 400 or 500).
- If a parameter (`username` or `message` or `id`) is missing, respond with some kind of
error (HTTP code 400 or 500)
- If username is longer than 15 bytes, respond with some kind of error (HTTP
code 400 or 500)
- If message is longer than 15 bytes, respond with some kind of error (HTTP
code 400 or 500) – reactions are intended to be short!
- If a reaction would make a chat have more than 100 reactions, the server
should respond with an error (HTTP code 404 or 500)

### `/reset`

A `/reset` request _resets_ the chat server to have no chats or reactions,
starting from the empty initial state. Should respond with a successful HTTP response with an empty body.

It should be possible to `/reset` the room many times, and after resetting the
memory usage of the program should be the same as in the empty initial state.

After a `reset`, it should be possible to immediately shut down the program and
have `valgrind` report no memory leaks.

## Design Questions
**You do not need to answer these for the resubmission**

1. How much working memory do 10 chats take in your program, in between
processing requests (assume no one has reacted to them)? How about 100? 1000? We
can call this part of the memory your program uses the _chat storage_. How much
additional working memory is used when handling the `/chats` request in your
code for 10, 100, and 1000 chats? Speculate on ways to lower either the _chat
storage_ or the memory used to process a request, or explain why your approach
minimizes them.

2. The PA writeup specifies many limits and constraints on the input (usernames,
messages, ids, and so on). Choose one of these limits or constraints, and
imagine removing it. What's something that would now work and might make a user
happy because the limit is removed? What's a problem that could result from
removing that limit? What impact would it have on your implementation to remove
it (any new possibilities of errors, new cases to handle, etc)?

## Implementation Guide

This page is the entire _specification_ for the assignment; it's what you need
to implement. You are free to make whatever choices you like in your code within
these constraints. To help you on your way, we have an _implementation guide_:

- A lot of the background you need is in Lab 5 [Part 2](https://ucsd-cse29.github.io/fa24/week5/header-intro.html) and [Part 3](https://ucsd-cse29.github.io/fa24/week5/number-server.html). Make sure you're comfortable with and have completed those ideas.
- Discussion sections [this
week](https://ucsd-cse29.github.io/fa24/index.html#week-5--managing-heap-memory)
will cover examples related to parsing query parameters in requests
- [HTTP](./http-server.md)
- [Function-by-function Breakdown](./data-vs-requests.md)
- [Representing Chats and Reactions](./representations.md)
- [Other Useful Functions](./helpful-functions.md)

## Handin

- Hand in your repository on Gradescope
- Make sure `make chat-server` builds your server (that's the command we will run), and the server runs on a predictable port with, for example, `./chat-server 8000` 
- Don't forget `DESIGN.md` and `CREDITS.md`
