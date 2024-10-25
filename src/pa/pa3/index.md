# PA3 - Web Server

## Web Servers and HTTP

[HTTP](https://en.wikipedia.org/wiki/HTTP) is one of the most common protocols
for communicating across computers. At the systems programming level, this means
using _system calls_ (usually in C) to tell the operating system to send bytes
over a network.

One nice feature of HTTP is that it is a primarily text-based protocol, which
makes it easy for humans to read and debug. It is also well-understood by web
browsers and programs like `curl`, making it easy to test and connect to
user-facing devices.

It's useful to get experience with the format of HTTP, and with using system
calls in C to manipulate HTTP requests.

## Task – Chat Server

In this programming assignment, you'll write a C program to implement a _chat
room_ (think a plain-text version of [Slack](https://slack.com/) or
[Discord](https://discord.com/)).

Your programs should compile and run with:

```
$ make chat-server
$ ./chat-server
```

### Chat Server

The server should start with `./chat-server` and print a single message:

```
$./chat-server
Server started on port PPPPP
```

It should continue running, listening for requests on that port, until it
receives a `/shutdown` request.

#### `/chats`

A request to `/chats` responds with the plain text rendering of all the chats.

The rendered chat format is

```
#NNNNN 20XX-MM-DD HH:MM  <username>: <message>
                      (<rusername>)  <reaction>
```

Where:

- `#NNNNN` is `#` followed by a number like `#5`, where the integer is the id of the
chat (ids start at 1 and count up)
- `YYYY-mm-dd HH:MM` is the _timestamp_ of the chat (when it was sent).
    - `YYYY` is the year, like `2024`
    - `mm` is the two-digit month, like `10` for October
    - `dd` is the two-digit day, like `31`
    - `HH` is the two-digit hour in 24-hour format, like `14` for 2pm
    - `MM` is the two-digit minute, like `55`
- `<username>` is the username of the user who sent the chat (without the
surrounding `<>`). It should always have the *last* character rendered in column 35 and the colon rendered at column 36
- `<message>` is the text of the message the user entered. It should always start on column 38
- `<rusername>` is the name of a user who reacted to the message. It should always be in parentheses with the close parenthesis in column 35
- `<reaction>` is a _reaction_ to a message

So an example chats rendering might look like:

```
#00001 2024-10-06 09:01         joe: hi aaron
#00002 2024-10-06 09:02       aaron: sup
#00003 2024-10-06 09:04         joe: working on the example chat for the PA
#00004 2024-10-06 09:06       aaron: oh cool what should it say
#00005 2024-10-06 09:07         joe: I dunno we could go pretty meta with it? I pushed an example go check it out. like a chat about the chat
#00006 2024-10-06 09:10       aaron: eh kinda lame tbh
#00007 2024-10-06 09:11         joe: whatever I already wrote it, going with it as-is
#00008 2024-10-06 09:12       aaron: ok but make sure we don't look like jerks
#00009 2024-10-06 09:12       aaron: or at least not me
                              (joe)  👍🏻 
#00010 2024-10-06 09:12         joe: good talk
```


Here's another:

```
#00001 2024-10-24 13:01        yash: hi all! react with 👍🏻 if you think the lab is good to go, or 😬 if you think it needs more testing
                            (aaron)  👍🏻 
                            (elena)  😬 
                           (arunan)  😬 
                            (janet)  😬 
                           (travis)  😬 
                              (joe)  🐿️
#00002 2024-10-24 13:02        yash: OK we'll go with what joe said
```

#### `/send`

A `send` request looks like this:

`/send?user=<username>&message=<message>`

This creates a new chat with the given username and message string with a
timestamp given by the time the request is received by the server.  Responds
with the list of all chats (including the new one).

This uses the standard format for [URL parameters and query
strings](https://en.wikipedia.org/wiki/Query_string). You should not try to
parse this yourself; see [FILL] for how to handle this.

If message is longer than 1000 bytes, only the first 1000 bytes are used as part
of the message.

If username is longer than 12 bytes, only the first 12 bytes are used as the
username

#### `/react`

```
/react?user=<username>&reaction=<reaction>&id=<id>
```

Creates a new *reaction* to a chat by the given username with the given message
string, reacting to the post with the given id (the ids are the `#NNNNN` at the
beginning of posts)

If reaction is longer than 16 bytes, only the first 16 bytes are used as part
of the reaction.

If username is longer than 12 bytes, only the first 12 bytes are used as the
username

#### `/reset`

A `/reset` request resets the chat server to have no chats or reactions,
starting from the empty initial state.

It should be possible to `/reset` the room many times, and after resetting the
memory usage of the program should be the same as in the empty initial
state.
