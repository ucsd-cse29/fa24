# Viewing and Redirecting Program Output

In the starter code, you are given a problem.c source code file. This program creates a large 2-D array, fills it with numbers, and prints them out. Fortunately, whoever wrote this was thoughtful enough to write code to check for an out-of-bounds error. Unfortunately, whoever wrote this was not thoughtful enough to debug the program. We’re going to use this program as an example of how the following UNIX commands can be used to parse *a lot* of program output easily.

Compile and run problem to see exactly what “a lot of program output” means.

```
$ make problem
$ ./problem
```

You will notice that the program occassionally prints out an error amidst all the other output of the program. For programs with more errors and more output, you could imagine how we wouldn’t want to keep scrolling up the terminal to read. There are multiple ways in which we can filter out everything but the error messages.

## Say `less`

During the quarter, you have used *indirection* (`<`) and *redirection* (`>`) operators to read from and write to files. Let’s first save the output of the program to a text file:

```
$ ./problem > problem.txt
```

You have also seen the `cat` command to print out the contents of a file. However, if the file is too large, it can be difficult to read. Instead, you can use the `less` command to view the contents of a file one page at a time:

```
$ less problem.txt
```

**TASK:**
1. Use `less` to view the contents of `problem.txt`. 
2. Hit `h` when viewing the file with `less` to see the help menu for a list of all other subcommands you can use
3. Determine the subcommand to filter out all lines that do not contain the word `error` by using the help menu
4. **IN YOUR NOTES:** Provide a screenshot of the output of `less` with only the `error` lines showing.

## `grep`

The grep command is most commonly used to search for lines of a file that match some string. `grep` takes in two arguments: the string to match and a file to read from.

```
$ grep error problem.txt
```

This command directly outputs to the terminal, which can be acceptable if you expect the output to be short, and helpful if you don’t want to run the search as a subcommand within another program, as with `less`. You can of course redirect the output of `grep` to a file and then use `less` to view the filtered output.

**TASK:**
1. We have provided an additional file named `message.txt` in your starter code. 
2. This file contains the output of another command, which created a large array, assigned random capital character values, and printed it out. Some of these values were written way out of bounds at column index **42** and we want to find all these out of bounds entries.
3. Using `less` and/or `grep`, search for all the lines that contain the string `42` in `message.txt`.
4. **IN YOUR NOTES:** Provide a screenshot of your search results and the message that was hidden in the out of bounds entries.

## Output Streams

In the examples above, we use redirection to manipulate the standard output (`stdout`) of a program. By default, `printf()` outputs to this `stdout` stream, which we illustrate above. What these diagrams do not show is that there actually exists another output stream called standard error (`stderr`).

To use `stderr`, we use an alternative to `printf()`, `fprintf()`, and specify that it should output to the `stderr` stream. In `problem.c`, this line is given to you and commented out. Uncomment this line, and comment the line above (the original print statement). Recompile the program.

**TASK: Write your observations for each step in your notes and compare!**
1. Run the program with no output redirection (`$ ./problem`) and observe the output. What do you notice?
2. Run the program with output redirection to a file (`$ ./problem > problem.txt`) and observe the output. What do you notice? What is the difference between what's in the file and what's on the terminal?
3. Run the program with output redirection to a file (`$ ./problem 2> errors.txt`) and observe the output. What do you notice?

UNIX uses `1>` implicitly as the default redirection operator when we just use `>`. We can read this as “*redirect to the stream with file descriptor 1*”, where the stream with file descriptor 1 is `stdout`. Similarly, `2>` redirects to the stream with file descriptor 2, which is `stderr`.

We can also use two redirections in conjuction with each other to redirect different streams to different files in one command.

```
$ ./problem > problem.txt 2> errors.txt
```

Or we can redirect both streams to the same file.

```
$ ./problem > output.txt 2>&1
```
where this syntax is read as “*redirect the stream with file descriptor 2 to the same place as the stream with file descriptor 1*”.
