# Working Incrementally: Data vs. Requests

One way to break down the work the server needs to do is:

- Parsing and interpreting requests (is the request a new post, a reaction, etc)
- Updating the current data (chats and reactions) based on the parameters in the request
- Responding to requests based on the current state of the data (chats and requests)

One way to work incrementally is to separate the *data handling* and the
*request handling* parts into different functions.

The *data handling* functions can be tested with `assert`s, and the *request
handling* can be tested with `curl` or a client.

We think the following functions might be useful for you to implement. In your
program you might have slightly different signatures or ideas, but these are a
useful starting point. Also, our staff is more familiar with this approach, so
it will take us less time to help you in office hours!

## Data Handling Functions

These functions can be written and tested without starting a server at all. You
could consider having a separate `main` function in its own file that just tests
these!

### `add_chat`

A function `add_chat` can add a single chat.

```
uint8_t add_chat(char* username, char* message)
```

This function might have several tasks:

1. Update the current `id`
2. Get the current timestamp
3. Create a new chat and fill in its username and message fields
4. As needed, allocate new space, put the new chat in heap memory, store a
reference to it in an array, etc. depending on your specific representation of
chats

This is testable by setting up initial states of chats and reactions, running
the function, and then using `assert` or `printf` on the results.

### `add_reaction`

Similar to `add_chat`, this adds a single reaction:

```
uint8_t add_reaction(char* username, char* message, char* id)
```

This function might have several tasks:

- Use the id to locate the chat that this reaction is for (and maybe return
early with an error if the id is invalid/out of range)
- Create a new reaction and fill in its username and message fields
- Add the reaction to the chat struct somehow, maybe with newly allocated space,
an added element or reference in an array, etc. depending on your specific representation of chats and reactions
- Update the count of reactions on the referenced chat

This is testable by setting up initial states of chats and reactions, running
the function, and then using `assert` or `printf` on the results.

### `reset`

This function can use `free` as necessary to clear dynamically-allocated heap
memory and reset logical values (like a counter of the number of chats) back to
0.

This is testable by setting up initial states of chats and reactions, running
the function, and then using `assert` or `printf` on the results. You can also
set up a `main` function in a fresh file just for checking that after using a
sequence of `add_chat` and `add_reaction` followed by reset, there are no memory
leaks when run with `valgrind`.

## Request and Response Handling Functions

You will definitely need to write a function for handling responses. But the
work of handling individual responses can be broken up. One approach could be to
get the path and query parameter string from the request and check if it's path
is `/post`, `/chats`, etc, then pass the string to other functions

### `respond_with_chats`

```
void respond_with_chats(int client)
```

This function is reponsible for using `write` or `send` to send the response to
the client that made the request. It might include:

- Using `snprintf` to format strings with data from the timestamp or ids
- Calling `write(client, str, size)` on various strings (with the appropirate size) to directly send the data to the client

### `handle_post`

```
// path is a string like "/post?user=joe&message=hi"
void handle_post(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username and message from the path
- Call `add_chat` to do the data update
- Call `respond_with_chats` to send the response 

### `handle_reaction`

```
// path is a string like "/react?user=joe&message=hi&id=3"
void handle_reaction(char* path, int client)
```

This function can have several tasks:

- Use string functions to extract the username, message, and id from the path
- Call `add_reaction` to do the data update
- Call `respond_with_chats` to send the response 

## Parsing Functions

One crucial task is getting information out of requests. That is, given a string like this:

```
"GET /post?user=joe&message=hi HTTP/1.1\r\n"
```

How do we extract the parts that say `"joe"` and `"hi"`?

There are a few substeps you might consider, whether as helper functions or just parts of an overall approach:

- Isolate the path part (the part starting with `/` and up until the space before `HTTP`)
- Search for known strings and delimiters like `user=` and `&`
- Copy parts of the string into new character arrays, paying careful attention to the necessary lengths (some of the limits on requests may be helpful here!). Alternatively, create interior pointers into the path at the appropriate places for the username and message


Remember that [Week 4 Monday](https://ucsd-cse29.github.io/fa24/#week-4--representations-and-memory) had a video specifically about strings and interior pointers, and [Week 5 Discussions](https://ucsd-cse29.github.io/fa24/#week-5--managing-heap-memory) are specifically about parsing requests!
