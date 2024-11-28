
# Project 5: The Pioneer Shell

This assignment is from [CSE29
SP24](https://cse29sp24.github.io/docs/pas/pa6.html#acknowledgements), which has
its own list of acknowledgments!

## Learning Goals

This assignment calls upon many of the concepts that you have practiced in
previous PAs.  Specfically, we will practice the following concepts in C:

- string manipulation using library functions,
- command line arguments,
- opening, reading from, and writing to files,
- process management using fork(), exec(), and wait(), and of course,
- using the terminal and vim.

## Introduction

Throughout this quarter, you have been interacting with the ieng6 server via the
terminal – you’ve used `vim` to write code, used `gcc` and `make` to compile,
used `git` to commit and push your changes, etc. At the heart of all this lies
the shell, which acts as the user interface for the operating system.

At its core, the shell is a program that reads and parses user input, and runs
built-in commands (such as `cd`) or executable programs (such as `ls`, `gcc`, `make`, or
`vim`).

As a way to wrap up this quarter, you will now create your own shell (a
massively simplified one of course). We shall call it–

## The Pioneer Shell

The PIoneer SHell, or as we endearingly call it, `pish` (a name with such elegance
as other popular programs in the UNIX world, e.g., git).

### Interactive Mode

Your basic shell simply runs on an infinite loop; it repeatedly–

- prints out a prompt,
- reads keyboard input from the user
- parses the input into a command and argument list
- if the input is a built-in shell command, then executes the command directly
- otherwise, creates a child process to run the program specified in the input
command, and waits for that process to finish

This mode of operation is called the **interactive mode**. The other mode you will need to implement is–

### Batch Mode

Shell programs (like `bash`, which is what you have been using on ieng6) also
support a batch execution mode, i.e., scripts. In this mode, instead of printing
out a prompt and waiting for user input, the shell reads from a script file and
executes the commands from that file one line at a time.

In both modes, once the shell hits the end-of-file marker (EOF), it should call
`exit(EXIT_SUCCESS)` to exit gracefully. In the interactive mode, this can be done
by pressing Ctrl-D.

## Parsing Input

Every time the shell reads a line of input (be it from `stdin` or from a file),
it breaks it down into our familiar `argv` array.

For instance, if the user enters `"ls -a -l\n"` (notice the newline character),
the shell should break it down into `argv[0] = "ls"`, `argv[1] = "-a"`, and `argv[2]
= "-l"`. In the starter code, we provide a struct to hold the parsed command.

### Handling Whitespaces

You should make sure your code is robust enough to handle various sorts of
whitespace characters. In this PA, we expect your shell to handle any arbitrary
number of spaces (` `) and tabs (`\t`) between arguments.

For example, your shell should be able to handle the following input: `" \tls\t\t-a -l "`, and still run the ls program with the correct `argv` array.

To split the arguments is very much like what you did in PA3 parsing URLs. We give a
specific suggestion of a function for this PA:

### The `strtok()` function

```
char *strtok(char *str, const char *delim);
```

The `strtok()` function breaks a string into a sequence of zero or more nonempty
tokens. On the **first call** to `strtok()`, the string to be parsed should be
specified in `str`. In each subsequent call that should parse the same string, `str`
must be `NULL`. **Read that last bit again - `strtok` is not like other
functions we've used!**

The `delim` argument specifies a set of characters that delimit the tokens in the
parsed string.

Each call to `strtok()` returns a pointer to a null-terminated string containing
the next token. If no more tokens are found, `strtok()` returns `NULL`.

The above paragraphs are taken directly from the Linux manual (except for "read
that last bit again". Joe added that). Now let’s see this function in action:

Suppose we have the following string:

```
char str[32] = "A|BC|D E   |FGH   \n"
```

And we would like to break it down by any of `'|'`, `' '`, or `'\n'`, which would
leave us `"A"`, `"BC"`, `"D"`, `"E"`, and `"FGH"`. We can write the following code:

```
#include <stdio.h>
#include <string.h>

int main()
{
    char str[32] = "  A|BC|D E   |FGH   \n";
    // break down the string at '|', ' ', and '\n' delimiters.
    char *tok = strtok(str, " |\n");
    while (tok) {
        printf("\'%s\'\n", tok);
        tok = strtok(NULL, " |\n");
    }
    return 0;
}
```

And running this program gives us:

```
'A'
'BC'
'D'
'E'
'FGH'
```
Note again that we try to break down (tokenize) the string using three possible
delimiter characters: `'|'`, `' '`, or `'\n'`, the `delim` string we pass to `strtok()`
has these three characters: `" |\n"`.

We think you will find `strtok()` very useful for your implementation!


## Built-In Commands

Whenver your shell executes a command, it should check whether the command is a
built-in command or not. Specifically, the first whitespace-separated value in
the user input string is the command. For example, if the user enters `ls -a -l tests/`,
we break it down into `argv[0] = "ls", argv[1] = "-a", argv[2] = "-l",
and argv[3] = "tests/"`, and the command we are checking for is `argv[0]`, which is
`"ls"`.

If the command is one of the following built-in commands, your shell should
invoke your implmementation of that built-in command.

There are three built-in commands to implement for this project: `exit`, `cd`,
and `history`.

### Built-in Command: `exit`

When the user types `exit`, your shell should call the `exit` system call with
`EXIT_SUCCESS` (macro for `0`). This command does not take arguments. If any is
provided, the shell raises a usage error.

### Built-in Command: `cd`

`cd` should be run with precisely 1 argument, which is the path to change to.
You should use the `chdir()` system call with the argument supplied by the user.
If `chdir()` fails (refer to man page to see how to detect failure), you should
use call `perror("cd")` to print an error message. We will explain the
`perror()` function in a later section.

### Built-in Command: `history`

When the user enters the `history` command, the shell should print out the list of
commands a user has ever entered in interactive mode.

(If you are on ieng6, open the `~/.bash_history` file to take a look at all the
commands you have executed. How far you’ve come this quarter!)

To do this, we will need to write the execution history to a file for persistent
storage. Just like `bash`, we designate a hidden file in the user’s home directory
to store the command history.

Our history file will be stored at `~/.pish_history`. (You will find a function in
the starter code that help you get this file path.)

When adding a command to history, If the user enters an empty command (0 length
or whitespace-only), it should not be added to the history.

When the user types in the `history` command to our shell, it should print out
all the contents of our history file, adding a counter to each line:

```
▶  history
1 history
▶  pwd
/home/jpolitz/cse29fa24/pa5/Simple-Shell
▶  ls
Makefile  script.sh  pish  pish.c  pish.h	pish_history.c  pish_history.o  pish.o
▶  history
1 history
2 pwd
3 ls
4 history
```

Note that the number before each line is added by `history`. The contents of
`.pish_history` should not contain the leading numbers.

## Running Programs

If, instead, the command is not one of the aforementioned built-in commands, the
shell treats it as a program, and spawns a child process to run and manage the
program using the `fork()` and `exec()` family of system calls, along with
`wait()`.

Refer to the material from [Week
9](https://ucsd-cse29.github.io/fa24/#week-9--process-creation-and-control) for
information on these system calls.

## Excluded Features

Now because our shells are quite simple, there are a lot of things that you may
be accustomed to using that will not be present in our shell. (Just so you are
aware how much work the authors of the bash shell put into their product!)

You will not be able to

-use the arrow keys to navigate your command history,
-use <tab> to autocomplete commands,
-use the tilde character (~) to represent your home directory,
-use redirection (> and <),
-pipe between commands (|),
-and many more…

Don’t be concerned when these things don’t work in your shell implementation!

If this were an upper-division C course, we would also ask you to implement
redirection and piping, but it's *[checks notes]* week 10 already!

## Handling Errors

Because the shell is quite a complex program, we expect you to handle many
different errors and print appropriate error messages. To make this simple, we
now introduce–

### Usage Errors

This only applies to built-in commands. When the user invokes one of the shell’s
built-in commands, we need to check if they are doing it correctly.

- For `cd`, we expect `argc == 2`,
- For `history` and `exit`, we expect `argc == 1`.

If the users enters an incorrect command, e.g. `exit 1` or `cd` without a path,
then you should call the `usage_error()` function in the starter code, and
continue to the next iteration of the loop.

### The `perror()` function

```
void perror(const char *s);
```

The `perror()` function produces a message on `stderr` describing the last error
encountered during a library function/system call.

When printing the error message, `perror()` first prints whatever string `s` we
give it, followed by a colon and a blank, followed by the error message.

Consider an example where we try to open a nonexistent file using `fopen()`, the
call should fail and not return a valid `FILE` pointer, in which case, we call
`perror()` to report the problem:

```
FILE *fp = fopen("noexist.txt", "r");
if (fp == NULL) {
    perror("open");
    return EXIT_FAILURE;
}
```

If we run this program, we would get the following output:

```
open: No such file or directory
```

### Errors to handle

You need to handle errors from the following system calls/library functions
using `perror()`. Please pay attention to the string we give to `perror()` in each
case and reproduce it in your code exactly.

- `fopen()` failure: `perror("open")`,
- `chdir()` failure: `perror("cd")`,
- `execvp()` failure: `perror("pish")`,
- `fork()` failure: `perror("fork")`


## Getting Started

The starter code for this assignment is hosted on GitHub classroom. Use the
following link to accept the GitHub Classroom assignment:

Github Classroom: [https://classroom.github.com/a/ZT3W6c0Z](https://classroom.github.com/a/ZT3W6c0Z)


### The Code Base

You are given the following files:

- `pish.h`: Defines struct pish_arg for handling command parsing; declares functions handling the history feature.
- `pish.c`: Implements the shell, including parsing, some built-in commands, and running programs.
- `pish_history.c`: Implements the history feature.
- `Makefile`: Builds the project.
- `ref-pish`: A reference implementation of the shell. Note that in this version,
the history is written to `~/.ref_pish_history` rather than `~/.pish_history`, to
avoid conflict with your own shell program.

(Note: The reference implementation contains a few inconsistencies with the
write-up. For instance, the reference program does not report an error when
cding into a nonexistent directory. If such an inconsistency occur, please stick
to the writeup!)

## Running pish

First, run `make` to compile everything. You should see the `pish` executable in
your assignment directory.

To run `pish` in interactive mode (accepting keyboard input), type

```
$ ./pish
```

Or, to run a script (e.g., script.sh), type

```
$ ./pish script.sh
```

The same applies for the reference implementation `ref-pish`.

### `struct pish_arg`

In pish.h, you will find the definition of struct `pish_arg`:

```
#define MAX_ARGC 64

struct pish_arg {
  int argc;
  char *argv[MAX_ARGC];
};
```

In our starter code, all functions handling a command (after it has been parsed)
will be given a `struct pish_arg` argument.

## Hints

This project once more requires you to think carefully about incremental
development. There are many things to, how should you go about everything? In
what order? Here’s one possibile plan:

- Start from simple commands without any arguments, e.g., `"ls"`.
- After that, start implementing running programs with `fork` and `exec`.
- Implementing input parsing using `strtok()`. Think about how to break down the line and put it into `struct pish_arg`.
- Once command parsing is working, go on to implement the two simple built-in commands: `exit` and `cd`. Make sure to take care of error handling.
- Next, make sure you can parse commands with arguments, e.g., `"ls -a"`.
- Next, make sure you can handle arbitrary whitespaces.
- Make sure reading from a script file works just as well as from `stdin`.
- Once that’s working, you can finish implementing the `history` command.
- The list above is just a suggestion. You are of course encouraged to come up
with your own implementation plan. But the most important thing is that you
should have a plan!

Start early, start often!


### Valgrind

You have a lot of freedom for how to implement this PA. You do not necessarily need to use malloc, but if you use dynamic memory allocation at any point, make sure you free everything properly. We will include a valgrind test when grading your assignment. So make sure there are no memory issues! (Memory leaks, invalid read/writes, using uninitialized variables, etc.)


### Submission

- Submit your code to Gradescope
- We will run your program with `make` and `./pish` in both interactive and batch mode
- There are no design questions
- CREDITS.md is still required


















































