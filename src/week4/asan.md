# Debugging Memory Errors

1. On `ieng6`, put this program in a file called `wrongarg.c`:

```
#include <stdio.h>
int main(int argc, char** argv) {
  for (int i = 0; i <= argc; i++) {
    printf("%s\n", argv[i]);
  }
}
```

2. Then run the following command to compile the program:

```
$ gcc -std=c99 wrongarg.c -o wrongarg 
```
Notice the new command-line flag introduced here! We use the `-std=c99` flag to tell `gcc` what version of C we want to compile with. This is necessary since the default version on `ieng6` would fail to compile this program due to us declaring `i` within the `for` loop.

3. Next, we will run the program with a single command-line argument. What output do you get? Here's what I got:

```
$ ./wrongarg onlyone
./wrongarg
onlyone
Segmentation fault (core dumped)
```

When we provided a single argument, the command-line argument at index `2` is _invalid_ as an address (it happens to be `0`, though other values would givethe same error), so the program ended with a _segmentation fault_, which is a fancy term for “the program tried to access memory it shouldn't and was stopped by the operating system”. This is because our `for` loop iterates until `i <= argc`, which means it will try to access `argv[argc]`, which is one past the number of arguments passed in.

This is pretty different from an error like `ArrayIndexOutOfBounds` in a language like `Java`, which gives information like a stack trace and the value of the incorrect index. Because of C's focus on doing only what is necessary and giving low-level access to memory, this kind of mistake is permitted, for better or worse. Aside from causing numerous security vulnerabilities, these _memory errors_ are difficult to debug.

Thankfully, there are a few tools that help debug invalid memory accesses.

## AddressSanitizer

[AddressSanitizer (or ASan)](https://github.com/google/sanitizers/wiki/addresssanitizer) is a tool, built into `gcc` and other C compilers these days, that turns invalid memory accesses (the kind that give segfaults) into descriptive errors. 

1. Let's try compiling and running this program again, with a special compile option to enable the sanitizer:

```
$ gcc -std=c99 -g -fsanitize=address wrongarg.c -o wrongarg.asan
```

The `-fsanitize=address` part does extra work in the compiler to put special checks in to look for memory errors. The `-g` option we saw in lecture turns on some debugging information like line numbers in stack traces.
  
2. After compiling we can run the program like before:

```
$ ./wrongarg.asan onlyone
./wrongarg.asan
onlyone
ASAN:SIGSEGV
=================================================================
==16074== ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x7f7a641bde71 sp 0x7ffd022ff3b8 bp 0x7ffd022ff410 T0)
AddressSanitizer can not provide additional info.
    #0 0x7f7a641bde70 in __GI_strlen (/lib64/libc.so.6+0x8ce70)
    #1 0x7f7a641a1751 in _IO_puts (/lib64/libc.so.6+0x70751)
    #2 0x400703 in main /home/linux/ieng6/cs29fa24/cs29fa24zq/wrongarg.c:4
    #3 0x7f7a64153554 in __libc_start_main (/lib64/libc.so.6+0x22554)
    #4 0x4005e8 in _start (/home/linux/ieng6/cs29fa24/cs29fa24zq/wrongarg.asan+0x4005e8)
SUMMARY: AddressSanitizer: SEGV ??:0 __GI_strlen
==16074== ABORTING
```

The key thing is it has a _stacktrace_, (a list of function calls that led to the error) which specifically points to `wrongarg.c:4`, or line 4 of the file `wrongarg.c`.

**In your notes:** Try passing in more than one argument to the program. What happens? Why do you think this is the case?

**Q**: Why isn't ASan the default? 

**A**: Mainly because it makes programs significantly slower. On small test cases and inputs that's not a big deal, so it's great for debugging, or for deploying in an environment where speed isn't an issue. But if you're trying to hash as many passwords as you can in 10 seconds, it's best to not turn it on! 
So there's a good reason to have the option to compile two different executables, which we called `wrongarg` and `wrongarg.asan` above.

## GDB
Another tool that can help us debug memory errors is one we have been using a little bit already: `gdb`. 
`gdb` is a command-line debugger that allows us to step through our program line by line and inspect the values of variables at each step. It can also give us backtraces through our program to show us where the error may have occurred.

If we compiled our source files with the `-g` command, we can run gdb with our debugging program with:
``` 
$ gdb wrongarg.asan
```

Before running the program, set a **breakpoint** in the code before the program reaches its error. Here, the error is on line 3, so type in your gdb terminal:
``` 
(gdb) break main.c:4
```

After setting the breakpoint, run the program from gdb with the same arguments we used prior
``` 
(gdb) run onlyone
```

If done correctly, `gdb` should print out the `printf()` line in the program. The breakpoint paused the execution before this line was executed.

* The `bt` command prints out the same stacktrace seen when running ASan.

* The `info` command can tell us some useful information at this point in the program. `info args` tells us what arguments were passed into this function, `info locals` tells the values of the local variables at this point of the execution.
* The `p` command prints the value of a variable/address. `p` can take an extra arguement to specify how the output should be formatted. (e.g. `p/x var1` prints the value of `var1` in hex, `p/t var1` prints in binary).

**Task:** Run `info args` in the gdb terminal, what do you see?

**In your notes:** Print the value of the variable that `wrongarg.c` is attempting to access. Add the command you used to your notes along with what `gdb` printed out.
