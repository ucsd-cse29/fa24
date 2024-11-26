# Pokemon Mailtime!

The `mail` command, unlike other commands we’ve taught you in this lab and previous ones, is especially unique: *literally no one* uses this! As such, this section is not relevant to any course material. But the idea of sending each other mail via the terminal, all 1970s-core, is too appealing to pass up on.

## Using the `mail` Shell

Throughout this section, we’ll use `myname` and `friendname` to refer to your and your partner’s UCSD username, respectively. This is the username you use for your UCSD email, and the one you use to log into `ieng6`.

In order for mail to work, you and whoever you are mailing to must be on the same cluster on `ieng6`. If each line of your command prompt starts with this:

```
[myname@ieng6-203]:~:500$
```

then `ieng6-203` is the cluster you are logged into. In order to SSH into a specific cluster, exit out of your current SSH session, and in your local machine terminal, type:

```
$ ssh myname@ieng6-203.ucsd.edu
```

You can choose between clusters 201, 202, and 203, as long as you make sure you and your partner are in the same cluster.

Once you and your partner are in the same cluster, try using the mail command to begin composing an e-mail:

```
$ mail friendname@ieng6-203.ucsd.edu
```

This will prompt you with `Subject:` so you can type your email’s subject. The subject is only one line of text, so when you press `Enter` you are now typing the contents of your mail. When done writing your message, press `Ctrl + D` to finish and send.

Now, your partner can use the `mail` command by itself to see that they have received mail! It will have a number next to it as it enumerates messages every time you open the mail shell. Type this number and press `Enter` to see the message!

While in the `mail` shell, you can type `?` to see a list of commands you can use to navigate your mail.

You will likely not need to use all of these commands but at least a few are worth noting:

- `type <message list>` can be used to print out the contents of selected messages. For example, `type 3 4` prints out the contents of messages 3 and 4.
- `headers` will print out the list of enumerated messages along with their senders, subjects, and statuses.
- You can respond to a message with `Reply <message list>`, which will open a response to the message to type in a reply. Again, you can finish and send with `Ctrl + D`. For example, `Reply 5` opens a response to message 5.


### Sending Mail from outside the `mail` Shell

There also exists another method to send mail from outside the `mail` shell, using the pipe operator (`|`) we learned earlier. 

This command also makes use of the `echo` command, which outputs its argument to `stdout` (`echo "hello"` will print hello to your terminal!). Sounds redundant, but it’s intended to be used in this way to input strings into other commands, or to be used as print statements in bash scripts.

```
$ echo “email body here” | mail -s “subject here” friendname@ieng6-203.ucsd.edu
```

### Trading Pokemon

For this section, you will be using the files within the `pokemon` directory of the starter code. This directory contains a `pokeget.sh` file which will generate a Pokemon when given its Pokedex number (don't worry if you don't know what that is, it's just a unique number for each Pokemon). The format to use the script is as follows:

```
$ ./pokeget.sh <Pokedex number> > <filename>.pk
```

#### Sender Tasks
1. Use the `pokeget.sh` script to generate a Pokemon of your choice and save it to a file. You can do this by running the script with the Pokedex number of the Pokemon you want to generate. For example, to generate Pikachu, you would run `./pokeget.sh 25 > pikachu.pk`.
2. Once you have generated your `.pk` file, use the following command to send your it to your partner, using the `-a` option. Replace `pikachu.pk` with the name of your Pokemon file if it is different.
```
$ echo "email body here" | mail -s "subject here" -a pikachu.pk friendname@ieng6-203.ucsd.edu
```

#### Receiver Tasks
1. Open your `mail` shell from within the `pokemon` directory and check for new mail. You should see the email with the Pokemon file attached.
2. Save the email to a file in the `pokemon` directory by typing `save <message number> pikachu.email`. For example, if the message number is 3, you would type `save 3 pikachu.email`.
3. Extract the attachment to retrieve the Pokemon that you were sent using the provided script:
```
$ ./extract_pokemon.sh pikachu.email > pikachu.pk
$ cat pikachu.pk
```
> NOTE: the filenames here aren't official or necessary, we just picked them to make it easier to keep track of what kinds files things are

If everything went well, you should see get the Pokemon your partner sent you! Have a bit of fun with this and send each other some cool Pokemon.
