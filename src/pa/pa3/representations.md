# Representing Chats

Chats and reactions both have multiple fields, so a natural choice is to
represent both chats and reactions as structs.

A chat has several components, which may be good candidates for struct fields:

- The message
- The username
- The timestamp
- The reactions to the message

A reaction has the message content and the user who posted it (no timestamp or
reactions-to-reactions), both of which are fixed-size.

You could consider structures like these; what are some tradeoffs? (We've
assumed that the program defines some useful constants to avoid repeating
specific numbers).

```
struct Reaction {
    char user[USERNAME_SIZE];
    char message[REACTION_SIZE];
}
struct Chat {
    uint32_t id;
    char user[USERNAME_SIZE];
    char message[MESSAGE_SIZE];
    char timestamp[TIMESTAMP_SIZE];
    uint32_t num_reactions;
    Reaction reactions[MAX_REACTIONS];
}
```

```
struct Reaction {
    char *user;
    char *message;
}
struct Chat {
    uint32_t id;
    char *user;
    char *message;
    char *timestamp;
    uint32_t num_reactions;
    Reaction *reactions;
}
```

These are ideas – some combination of them might work, and they are not necessarily perfect or complete. Some things to think about:

- Which fields are fixed-size?
- Which fields can grow?
- Which fields can change?
- What are limits for them described in the specification?







