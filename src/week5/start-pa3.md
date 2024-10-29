# Introduction to PA3

Entering lab, you may have noticed something interesting running on the projector. We've started up a demonstration of the next PA to play around with.
For the next PA, you'll be creating your own chatroom server, where users can send and react to other's messages.

We've included a client on the `ieng6` machines that you can use to communicate in our chatroom.

We can run our chat-client with:
```
/home/linux/ieng6/<cse folder>/public/chat-client <username> <machine> 8000
```
For Joe's lab use:
* \<cse folder\> - cs29fa24
* \<machine\> - ieng6-201

For Aaron's lab use:
* \<cse folder\> - cs29fa24b
* \<machine\> - ieng6-202

**Task:** 
1. Choose a username and send a message to your lab room's chat server.
2. Try reacting to a member of your lab group's message. Try reacting with an emoji 😁
3. **In your notes:** Add a screenshot of your message and reaction.
---
The client is cool, but there are many other ways we can also interact with the chat server:
 In the past we've been using `curl` primarily to download single files from the internet. We can also use `curl` to send messages!

To see all the messages of the chat server we can curl the url:
```
curl <machine>.ucsd.edu:8000/chats
```


To send a message to the chat server, we can curl the url:
```
curl <machine>.ucsd.edu:8000/send?user=<username>&message=<message>
```
**Task:** 

3.  Try sending a message to the chatroom server using `curl`


To react to another user's message, we can curl the url:
```
curl <machine>.ucsd.edu:8000/react?user=<username>&reaction=<reaction>&id=<id>
```
\<reaction\> can be any 16 byte message and \<id\> is the id of the message you wish to react to. 

**Task:** 

3. Try reacting to your group member's message from your web browser (Chrome, Safari, Firefox, etc.)
4. **In your notes:** Add a screenshot from your web browser of `<machine>.ucsd.edu:8000/chats`.