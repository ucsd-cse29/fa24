Entering lab, you may have noticed something interesting running on the projector. We've started up a demonstration of the next PA to play around with.
For the next PA, you'll be creating your own chatroom server, where users can send and react to other's messages.

In the past we've been using `curl` primarily to download single files from the internet. We can also use `curl` to send messages to other machines!

To see all the messages of the chat server we can curl the url:
```
curl <host>:8000/chats
```
The \<host\> is `ieng6-201.ucsd.edu` for Joe's lab, and `ieng6-202.ucsd.edu` for Aaron's lab.

To send a message to the chat server, we can curl the url:
```
curl <host>:8000/send?user=<username>&message=<message>
```
**Task:** 
1. Choose a username and send a message to your lab room's chat server. First use `curl`, then try to make the same request through your web browser.

2. Try sending non-ASCII characters in your message. Does it work?

To react to another user's message, we can curl the url:
```
curl <host>:8000/react?user=<username>&reaction=<reaction>&id=<id>
```
\<reaction\> can be any 16 byte message and \<id\> is the id of the message you wish to react to. 

**Task:** 

3. React to a message from one of the other members of your lab group.
4. **In your notes:** Add a screenshot of your message. Also include the reaction(s) you added in your screenshots.



