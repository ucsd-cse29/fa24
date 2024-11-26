# Flow like Water with Pipes

The searching and filtering methods we have seen thus far require that the output of a program be saved to a file before we can manipulate it. However, there are times when we want to filter the output of a program without saving it to a file. This is where pipes come in!

Within UNIX, the pipe operator (`|`) is used to directly feed output from one program as input into another program. We can pipe directly from the problem program into either `less` or `grep` to accomplish the same result as running these commands on the `problem.txt` file:

```
$ ./problem | less
$ ./problem | grep error
```

We can compound indirection, redirection, and pipe operators to create helpful commands. Understanding how these operators work in conjunction with each other can be understood as an analogy to actual pipes, rendered below in immaculate ASCII art.

- By default, print statements in programs output directly to the terminal interface. So this command:
    ```
    $ ./problem
    ```

    looks like this:
    ```
    +-----------+
    |           |==
    | ./problem | ~ ~ ~ ~ ~> terminal
    |           |==
    +-----------+
    ```

- By using the redirection operator, we install an elbow pipe to redirect the flow of output into a file. The output no longer flows into the terminal.

    ```
    $ ./problem > problem.txt
    ```

    ```
    +-----------+  redirect
    |           |==------+    
    | ./problem | ~ ~ ~  |   terminal
    |           |==--+ $ +
    +-----------+    | $ |
                     | v |
                 problem.txt
    ```

- By using the pipe operator, we install a coupling between the output and input of two programs. Without any other pipes at the end, the output of the second program flow into the terminal.

    ```
    $ ./problem | grep error
    ```

    ```
    +-----------+   pipe    +-----------+
    |           |==-------==|           |==
    | ./problem | ~ ~ ~ ~ ~>|   grep    | ~ ~ ~ ~ ~> terminal
    |           |==-------==|           |==
    +-----------+           +-----------+
    ```

- By using both piping and redirection, we can chain multiple commands and file writing actions. In this command, we run the problem program, filter its output with `grep`, and output the filtered lines into a file. This file now contains the error messages from problem, and can serve as an error log. 
**IN YOUR NOTES:** Does this output to the terminal as well?
    ```
    $ ./problem | grep error > errors.txt
    ```

    ```
    +-----------+   pipe    +-----------+  redirect
    |           |==-------==|           |==------+
    | ./problem | ~ ~ ~ ~ ~>|   grep    | ~ ~ ~  |   terminal
    |           |==-------==|           |==--+ $ +
    +-----------+           +-----------+    | $ |
                                             | v |
                                         errors.txt
    ```

## Exploring `grep`

<!-- Want to put some kind of grep exercise that involves pipes here, need to come up with something -->

