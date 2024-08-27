# Week 2 – URLs and Servers

## Lecture Materials

- [Monday Lecture Handout (Slides)](https://docs.google.com/presentation/d/13ESz6G6UVoTLbnJ6oopGWwxY--_oyNCS/edit?usp=sharing&ouid=109342588918218787603&rtpof=true&sd=true)
- [Monday Lecture Handout (PDF)](https://drive.google.com/file/d/1QXV2eEYmHIomcpHdX2zoKZvXnPJ_5Vkd/view?usp=sharing)
- [Wednesday Lecture Handout (Slides)](https://docs.google.com/presentation/d/13M_vMvQkkb0rYri1eQnYOOAAjlZaQ4aa/edit?usp=sharing&ouid=109342588918218787603&rtpof=true&sd=true)
- [Wednesday Lecture Handout (PDF)](https://drive.google.com/file/d/1dQAk0ZE7-CkXFkmMoBsW0e9_kScWKWwH/view?usp=sharing)
- Wednesday Notes <iframe src="https://drive.google.com/file/d/1gorjwpGTUoLRLBJ6yZdJbe7PLKEgfF4a/preview" width="100%" height="600px"></iframe>

## Lecture-Length Videos

This video about URLs takes the place of Monday's lecture and helps get set up
for Quiz 2:

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/MvUZjQX4yhM?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Video Shorts

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/8rFJhqzjTZo?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/BsVXb9eEkDM?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/FN6K9YvdhTA?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/ftVNZNL45GU?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Lab Tasks

As usual, you can read ahead and are encouraged to prepare! Keep in mind that
the lab isn't guaranteed to be final until the day of the lab, and a lot of the
exercises are collaborative, so you can't truly “finish it ahead of time”.
    
Today we'll use some of what we learned about URLS to create a **web server**.

### Links
    
<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/in1QMOYk6Io?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/rDpgSpZyScY?cc_load_policy=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

### Remotely Connecting to CSE15L account

**In Your Group for 15 minutes**

Many courses in CSE use course-specific accounts. These are similar to accounts
you might get on other systems at other institutions (or a future job). We'll
see how to use the terminal in EdStem.

Open a terminal in EdStem. To use `ssh`, your command will look like this, but
with the `user` replaced by your specific TritonLink username.

```
$ ssh user@ieng6.ucsd.edu
```

Since this is likely the first time you've connected to this server, you will
probably get a message like this:

```
$ ssh user@ieng6.ucsd.edu
The authenticity of host 'ieng6.ucsd.edu (128.54.70.227)' can't be established.
RSA key fingerprint is SHA256:ksruYwhnYH+sySHnHAtLUHngrPEyZTDl/1x99wUQcec.
Are you sure you want to continue connecting (yes/no/[fingerprint])? 
```

I (Joe) always say yes to these messages when I'm connecting to a new server for
the first time; it's expected to get this message in that case. If you get this
message when you're connecting to a server you connect to _often_, it could mean
someone is trying to listen in on or control the connection. This answer is a
decent description of what's going on: [Ben Voigt's
answer](https://superuser.com/questions/421074/ssh-the-authenticity-of-host-host-cant-be-established/421084#421084)

So type `yes` and press enter, then type the password for your TritonLink user account; the whole interaction
should look something like this once you give the password and are logged in:

```
# On your client
$ ssh user@ieng6.ucsd.edu
The authenticity of host 'ieng6-202.ucsd.edu (128.54.70.227)' can't be established.
RSA key fingerprint is SHA256:ksruYwhnYH+sySHnHAtLUHngrPEyZTDl/1x99wUQcec.
Are you sure you want to continue connecting (yes/no/[fingerprint])? 
Password: 
```

```
# Now on remote server
Last login: Sun Jan  2 14:03:05 2022 from 107-217-10-235.lightspeed.sndgca.sbcglobal.net
quota: No filesystem specified.
Hello user, you are currently logged into ieng6-203.ucsd.edu

You are using 0% CPU on this system

Cluster Status 
Hostname     Time    #Users  Load  Averages  
ieng6-201   23:25:01   0  0.08,  0.17,  0.11
ieng6-202   23:25:01   1  0.09,  0.15,  0.11
ieng6-203   23:25:01   1  0.08,  0.15,  0.11

To begin work for one of your courses [ cs15lwi24 ], type its name
at the command prompt.  (For example, "cs15lwi24", without the quotes).

To see all available software packages, type "prep -l" at the command prompt,
or "prep -h" for more options
```

Now execute the following command

```
$ cs15lwi24
```

(That's one, five, l (lowercase letter L, not one); the one and l look very
close in some fonts. And remember that when we write the `$`, that's not for you
to type in! It's just a convention for how we write commands.)

You should get the following output:

```
Sun Jan 02, 2022 11:28pm - Prepping cs15lwi24
```

Now your terminal is connected to a computer in the CSE basement, and any
commands you run will run on that computer! We call your computer the _client_
and the computer in the basement the _server_ based on how you are connected.

If, in this process, you run into errors and can't figure out how to proceed,
ask! When you ask, take a screenshot of your problem and add it to your group's
running notes document, then describe what the fix was. If you don't know how to
take a screenshot, ask!

Remember – it is **rare** for a tutorial to work perfectly. We often have to
stop, think, guess, Google search, ask someone, etc. in order to get things to
work the way the tutorial says. I look up the right way to describe the
`(yes/no)` answer on first login all the time, for example. So you are helping
your group _learn about potential issues_ when you do this, and that's a major
learning outcome of the course! If you see someone else have an issue that you
didn't, ask why, and what might be different about what you did, or how your
environment is set up. You will learn by reflecting on this.

**Write down in notes**: When you're done, **discuss** what you saw upon login.
Take a screenshot or copy/paste the output. Did you all see the same thing? What
might the differences mean? Note the results of your discussion in the notes
document.

### Meet Your New Group!

We have assigned you into groups that you will collaborate in for the rest of the
quarter. When you arrive at your lab, see the screen at the front of the room to
find your assigned seat.

**Write down in notes** – In your groups, share, and note in the running notes
document (discussion leaders, you answer these as well!):

- How you'd like people to refer to you (pronounce your name/nickname, pronouns
like he/her/they, etc)
- Your major
- One of:
    - A UCSD student organization you're a member of or interested in
    - Your favorite place you've found on campus so far
    - A useful campus shortcut or trick you know
- Your answer to the following question. Discuss why you chose that answer. ![Image](../../images/owls.png)

### The `URLHandler` Interface

There's a lot that web servers can do. We will start with a small fragment of
their behavior that is enough to do interesting work. For now we'll focus on
programs that take a URL as input and respond with the text of a web page. We'll
call the part of the program that does this processing a `URLHandler`:

```
interface URLHandler {
  String processRequest(URI uri);
}
```

We'll also use a class that takes a `URLHandler` and starts up the server that
listens for incoming connections.

```
class Server {
  static void start(int port, URLHandler handler) { ... }
}
```

(Note that it says `URI`, not `URL`. There isn't a meaningful difference between
these concepts for our purposes, and all the URIs we work with are also URLs.
Java has [good documentation on
URI](https://docs.oracle.com/javase/8/docs/api/java/net/URI.html). We'll discuss
what a `port` is below.).

We've provided an implementation of a web server that works with this interface here:

[https://github.com/ucsd-cse15l-f23/wavelet](https://github.com/ucsd-cse15l-f23/wavelet)

In your workspace—everyone can make their own—and clone that repository into it. Make sure you *aren't* logged in to `ieng6` when you do this clone. The first thing we do will be all on EdStem.

There are two files in this repository:

- `Server.java` – we (the staff) wrote this and you can treat it as a “black box”, without
understanding its details for today. Of course, you're welcome to read it and
ask questions about it, but we might defer your questions to Edstem, office
hours, or later to focus on the work specific to this lab.
- `NumberServer.java` – this is a program with a `main` method that creates a
`URLHandler` that manages a single number, and uses `Server.java` to start a web
server using that handler.

Read through the code in `NumberServer.java`. Discuss with your partner what you think each line or code block does. 

**Write down in notes** - What questions do you and your partner still have? It’s OK to have open questions at this point! Many will be resolved by the next few sections.

### Building and Running the Server

You can build and run the server in your EdStem workspace using these two
commands, from the directory created by cloning of the repository. (Remember, you might have to `cd` into that directory!) It should
look like this when it works:

```
$ javac Server.java NumberServer.java 
$ java NumberServer 4000
Server Started!
```

On EdStem, you can use the “Network” option in the menubar (it looks like the wifi symbol) and it will show you a link
you can use to visit the running web server:

![Network Menu](/images/network-menu-edstem.png)

This will open a new window or tab that looks something like this:

![Live website](/images/edstem-server-started.png)


There are a few definitions worth discussing here:

- **Ports**: The `4000` above identifies a specific _port_ that the web server
runs on. This is an extra part of a URL that's often used in development; `4000`
isn't special and you could pick others – you're welcome to try a few in the
thousands; it won't break anything.  Sites on the public web actually use a port
as well, either
[`80`](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol_) or
[`443`](https://en.wikipedia.org/wiki/HTTPS), but your browser hides it from you
because it's the default. You're welcome to read about these details, but they
aren't necessary to learn continue in this lab.

It's also worth pointing out that the terminal will just sit there without
letting you type more commands while the server is running: it is in an infinite
loop waiting for the next URL request to come in! You can stop the server by
pressing `Ctrl-c` (this works for any terminal command that's in an infinite
loop).

Try out URLs with paths and queries on the running server as described in
`NumberServer.java`. Based on the code, what paths and query combinations do you
think will have interesting effects? Try them out!

If you're stuck, a first one to try is the `/increment` path. To visit it, you can
**edit the URL bar in your browser directly** when visiting the server. Try adding `/increment` at
the end and then pressing Enter to load the page. What does it say? What other paths do you see in the code that you could try?

If you want another, try `/add`. What's different about using `/add` compared to `/increment`?

Try editing line 11 of `NumberServer.java` to include your name before the number is displayed. Example output:

```Edwin’s number: 3```

Because we’ve made a new change to our server, we need to restart the server for those changes to be displayed on the web browser. 
To stop the server, press `Ctrl-C`, then restart the server by running the same commands as earlier that we used to start it (`javac` and `java` commands). 

**Write down in notes** – show a screenshot of trying each of the paths that
provide a response based on your reading of `NumberServer.java`. There should be
4: the root path, one for incrementing, one for adding by a specific count, and
one that shows an error.

### Run the Server on a Remote Computer

Next, log into your account on `ieng6`. Then clone the same `wavelet` repository there.

Now, run your web server on `ieng6` using the same `java` and `javac` commands that you used to run it on your local machine. Note that there are only 3 ieng6 computers (you'll see that you've connected to
`ieng6-201`, `ieng6-202`, or `ieng6-203` in the prompt), which presents a
problem – each one only has one port `4000`. If multiple people try to use the
same port at the same time on the same computer, there will be an error:

```
# On remote server
[user@ieng6-202]:wavelet:123$ java NumberServer 4000
Exception in thread "main" java.net.BindException: Address already in use
        at sun.nio.ch.Net.bind0(Native Method)
        at sun.nio.ch.Net.bind(Net.java:461)
        at sun.nio.ch.Net.bind(Net.java:453)
```

So you can't *all* use port `4000`. If you want something unique for this lab
you can use `4000` + the number of the machine you're sitting in front of if in
room B260, and `7000` + that number if in room B270. Or experiment!

The cool thing about running it on these computers is you can access it from
other computers! After starting the server, you can load your web page from
other places! For example, if you're on `ieng6-201.ucsd.edu` running on port
1234, you can open `http://ieng6-201.ucsd.edu:1234` from another computer in the
lab or your laptop to see the output of the running server (this only works from
the UCSD network, so that means you'd need to be on the UCSD-Protected network).
Neat – you've deployed a web server!

**Write down in notes** - Team up with another member of your group that you haven't worked with yet.
Get their server URL and port number, and access their number server on
***your*** computer (**HINT**: You may want to share the URL and port number on
your group's Google Doc). Take a screenshot of ***your*** computer loading a webpage of
***their*** server, which should show the current number (though not their name!). Was their web server running on the same `ieng6` machine as yours? The same port?
<!-- Joe's answer: It’s stored on the heap as a field in a NumberServer object in the a Java process owned by "user" running on ieng6-201. -->

**Write down in notes** – If you have multiple browsers on different computers
all incrementing the number on one web server, do they all see one anothers'
increments? As accurately as possible, describe where the number is stored.

**Write down in notes** - Brainstorm a little bit. Now that you have the ability
to make a web server, what are some ideas for other applications you could
create? Think about things you could plausibly build with your knowledge of Java
plus this server interface.  What else might you need to go further?

**Write down in notes** – When you ran the server on `ieng6`, it didn't include your name (where you made it say `[Your Name] : <number>` on EdStem), even though you made that edit. Why not? What are things you could do, using only what we've seen in class so far, to get that version of the code on the server. Hint – you can make new public Github repositories yourself!

### Accessing URLs from the Command Line with `curl`

A web browser isn't the only way to access web pages. There are also commands
that can be used to access URLs. One of these commands is called `curl`. You
can use it like this:

```
curl https://raw.githubusercontent.com/ucsd-cse15l-w23/WhereAmI/main/WhereAmI.java
```

You could visit that URL in a web browser (to see some Java code from class),
_or_ run the `curl` command from the command line with the URL as an argument.
By default `curl` prints out what it accesses to the terminal.

You can also use `curl` to load the URLs for the server! It has the same
restrictions on access as whatever computer you're running it from. So that
means from the terminal on your local computer, a `curl` command would load
`ieng6-20x` URLs if you're connected to `UCSD-Protected`. But you can also log
into an `ieng6` server from your terminal and run `curl` from there, and use
that method to test your web server even if your laptop isn't on
`UCSD-Protected`. Try both things – using `curl` from your computer's local
terminal and from one logged into ieng6 to access your server.

Keep in mind this might mean you need to open _two_ terminals, one to start the
server and one to load the URL.

**Write down in notes**. Take a screenshot of two terminals, side-by-side, one
running the server and one loading a URL it serves via `curl`.


### Make the Simplest “Search Engine”

In your Edstem workspace, make a new file called `SearchEngine.java`. In it, implement a web server (like
`NumberServer.java`) that tracks a list of strings. It should support a path for
_adding_ a new string to the list, and a path for _querying_ the list of strings
and returning a list of all strings that have a given substring.

Examples of paths/queries:

```
/add?s=anewstringtoadd

/add?s=pineapple

/add?s=apple

/search?s=app
(would return pineapple and apple)
```

Discuss with your partner how you plan to add a new string to the list, query for it, and return a list of all strings with the given substring (as described above).

When you've implemented this (and even if you don't finish), make a note of the path for the code; we will use it and improve on it in future
labs.

**Write down in notes** – When you have something you want to share for your
search server, share the machine and port with others and try out one another's
servers! Can you have one person add some words that another person searches
for? As accurately as possible, describe where each list of strings is stored.


</div>
