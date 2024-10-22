# New Debugging Tools

For this section, you'll be working with the following program:



```
#include <stdio.h>

// edits string, then returns how many changed
int X_to_Y(char str[]) {
    int num_xes = 0;
    for (int i=0; str[i] != '\0'; i++) {
        if (str[i] = 'X') {
            str[i] = 'Y';
            num_xes += 1;
        }
    }
}

int main(int argc, char *argv[]) {
    for (int i=1; i<=argc; i++) {
        int num_xes = X_to_Y(argv[i]);
        printf("\"%s\": %d 'X'es changed\n", argv[i], num_xes);
    }
}
```

1. Read through this program *without runnning it*.
2. **In your notes**, write down what you think it would output if ran as `./buggy helloX XOXO` 
3. Discuss your thoughts with your group, and see if you notice any bugs in it. **In your notes**: Write down any bugs you think you've fonud.


4. On `ieng6`, use the following command to curl the above program into a file called `buggy.c`:

```
curl -o buggy.c https://raw.githubusercontent.com/ucsd-cse29/fa24/refs/heads/main/src/week4/buggy.c
```

4. Then run the following command to compile the program:

```
$ gcc -std=c11 buggy.c -o buggy 
```
Notice the new command-line flag introduced here! We use the `-std=c11` flag to tell `gcc` what version of C we want to compile with. This is necessary since the default version on `ieng6` would fail to compile this program due to us declaring `i` within the `for` loop.

5. Now, try running the program with some string arguments:

```
$ ./buggy helloX XOXO
```

Oh no! You should see it outputting far too many Y-s and zeroes, and then crashing (Segmentation Fault). Let's see if we can use -Wall to get to the bottom of this.

## The -Wall

Many common errors can be caught by the compiler, but a lot of these checks aren't enabled by default. We can ask the compiler to warn us about them with the `-Wall` flag ("- W(arn) all")

1. Run the following command to recompile the programm with warnings enabled:
```
$ gcc -Wall -std=c11 buggy.c -o buggy
```

2. This time, gcc should have given you two warnings, read through them. Would they have helped you catch those two bugs? **In your notes**: Write down the warnings you got (`[-Wxxxxxx]`)

In general, It's almost always a good idea to have `-Wall` enabled by default because it will helpfully warn you about many common C errors.

**NOTE**: One unfortunate side effect of `-Wall` is that if you ever declare a variable but don't use it, the compiler will warn you about it. This can be helpful to find bugs sometimes, but often ends up being more
annoying than helpful. You can disable this by with the `-Wno-unused-variables` flag:
```
gcc -Wall -Wno-unused-variables -std=c11 buggy.c -o buggy
```

## Segfaults

Now, we've found two bugs, but why is the program stil crashing? If we provide a single argument (argc=2), our`for` loop iterates until `i <= argc`, which means it will try to access `argv[argc]`, which is out of bounds.

Unfortunately, when we try to read this as a memory address (`char*`) , it ends up being an _invalid_ memory address (it happens to be `0`, though other values may give similar errors), so the program ended with a _segmentation fault_, which is a fancy term for “the program tried to access memory it shouldn't and was stopped by the operating system”. 

This is pretty different from an error like `ArrayIndexOutOfBounds` in a language like `Java`, which gives information like a stack trace and the value of the incorrect index. Because of C's focus on doing only what is necessary and giving low-level access to memory, this kind of mistake is permitted, for better or worse. Aside from causing numerous security vulnerabilities, these _memory errors_ are difficult to debug, since you can't even tell which line of code caused the crash.

Thankfully, there are a few tools that help debug invalid memory accesses.

## AddressSanitizer

Let's use the AddressSanitizer to figure out which line of code we crashed on. [AddressSanitizer (or ASan)](https://github.com/google/sanitizers/wiki/addresssanitizer) is a tool, built into `gcc` and other C compilers these days, that turns invalid memory accesses (the kind that give segfaults) into descriptive errors. 

1. Compile the program again with the following option to enable the sanitizer:

```
$ gcc -std=c11 -g -fsanitize=address buggy.c -o buggy.asan
```

The `-fsanitize=address` part does extra work in the compiler to put special checks in to look for memory errors. The `-g` option we saw in lecture turns on some debugging information like line numbers in stack traces.
  
2. After compiling, rerun the program like before. You should see it output a _stacktrace_ that start something like this, which shows the function calls that led to the error:

```
$ ./buggy.asan helloX
"YYYYYY": 0 'X'es changed
AddressSanitizer:DEADLYSIGNAL
=================================================================
==303858==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x55f690eb0320 bp 0x7fff2e028b50 sp 0x7fff2e028b30 T0)
==303858==The signal is caused by a READ memory access.
... (several lines omitted)
```

3. Read through the stack trace and identify the functions that were called. **In your notes:** Write down the last function called, and what line of buggy.c the error was on. 


Now, we can see exactly the path the code took before crashing, making our lives much easier! So, why isn't ASan the default? Mainly because it makes programs run slower. It's great for debugging, or for programs where speed isn't an issue, but if you're trying to hash as many passwords as you can in 10 seconds, it's best to not turn it on! For this reason, it's good to have the option to compile two separate executables, which we called `buggy` and `buggy.asan` above.

## GDB

Now that we've identified where the crash happens, let's use `gdb` to help us debug it further. 
`gdb` (which you've already seen a bit of in lecture / discussion) is a command-line debugger that allows us to step through our program line by line and inspect the values of variables at each step. It can also give us backtraces through our program to show us where the error may have occurred.

1. After compiling with the -g flag, load our program into gdb
``` 
$ gdb buggy.asan
```

2. Before running the program, set a **breakpoint** in the code before the program reaches its error. Here, the error is on line 6, so type in your gdb terminal:
``` 
(gdb) break buggy.c:6
```

3. After setting the breakpoint, run the program from inside gdb with 2 arguments (everything after `run` gets passed as command line args to your program)
``` 
(gdb) run helloX
```

If done correctly, `gdb` should print out the `for(int i=0...` line in the program. The breakpoint paused the execution before this line was executed.

4. Try the following commands
    * `info args`: tells us what arguments were passed into this function,
    * `info locals`: tells the values of the local variables at this point of the execution.
    * `p s[3]`: this lets your print out the values of expressions, not just variables. Try some others!
        * Can also specify the format you want, e.g. `p/x var1` prints the value of `var1` in hex, `p/t` prints in binary).
    * `bt` should print out a stacktrace similar to what ASan did.

5. Now, use the `c` command to continue executing until it hits the breakpoint a second time
6. Use the commands you learned to print the variable that `buggy.c` is attempting to access (and crashing on). **In your notes:** Write the command you used, and what `gdb` printed out
    * **NOTE**: If your program runs too far ahead, you can always ask gdb to restart it by using `run ARG1 ARG2 ...` again 
