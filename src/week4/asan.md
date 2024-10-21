# Debugging Memory Errors

On `ieng6`, put this program in a file called `wrongarg.c`:

```
#include <stdio.h>
int main(int argc, char** argv) {
  printf("%s\n", argv[2]);
}
```

Then run it, mimicking a situation where a programmer accidentally gives the
wrong number of arguments (here just one when 2 are expected):

```
$ gcc wrongarg.c -o wrongarg
$ ./wrongarg onlyone
```

What output do you get? Here's what I got:

```
$ ./wrongarg onlyone
Segmentation fault (core dumped)
```

When I provided a single argument, the command-line argument at index `2` is
_invalid_ as an address (it happens to be `0`, though other values would give
the same error), so the program ended with a _segmentation fault_, which is a
fancy term for “the program tried to access memory it shouldn't and was
stopped by the operating system”.

This is pretty different from an error like `ArrayIndexOutOfBounds` in a
language like `Java`, which gives information like a stack trace and the value
of the incorrect index. Because of C's focus on doing only what is necessary
and giving low-level access to memory, this kind of mistake is permitted, for
better or worse. Aside from causing numerous security vulnerabilities, these
_memory errors_ are difficult to debug.

Thankfully, there are a few tools that help debug invalid memory accesses.

## AddressSanitizer

[AddressSanitizer (or
ASan)](https://github.com/google/sanitizers/wiki/addresssanitizer) is a tool,
built into `gcc` and other C compilers these days, that turns invalid memory
accesses (the kind that give segfaults) into descriptive errors. Let's try
compiling and running this program again, with a special compile option to
enable the sanitizer:

```
$ gcc -g -fsanitize=address wrongarg.c -o wrongarg.asan
```

The `-fsanitize=address` part does extra work in the compiler to put special
checks in to look for memory errors. The `-g` option we saw in lecture, and it
turns on some debugging information like line numbers in stack traces.

After compiling we can run the program like before:

```
$ ./wrongarg.asan onlyone
ASAN:SIGSEGV
=================================================================
==14309== ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x7f3102d6fe71 sp 0x7fff24fa5a08 bp 0x7fff24fa5a50 T0)
AddressSanitizer can not provide additional info.
    #0 0x7f3102d6fe70 in __GI_strlen (/lib64/libc.so.6+0x8ce70)
    #1 0x7f3102d53751 in _IO_puts (/lib64/libc.so.6+0x70751)
    #2 0x4006ee in main /home/linux/ieng6/cs29fa24/cs29fa24/pa2-hashing-and-passwords-jpolitz/wrongarg.c:3
    #3 0x7f3102d05554 in __libc_start_main (/lib64/libc.so.6+0x22554)
    #4 0x4005e8 in _start (/home/linux/ieng6/cs29fa24/cs29fa24/pa2-hashing-and-passwords-jpolitz/wrongarg+0x4005e8)
SUMMARY: AddressSanitizer: SEGV ??:0 __GI_strlen
==14309== ABORTING
```

The key thing is it has a _stacktrace_, which specifically points to
`wrongarg.c:3`, or line 3 of the file `wrongarg.c`.

Q: Why isn't ASan the default? 
A: Mainly because it makes programs significantly
slower. On small test cases and inputs that's not a big deal, so it's great for
debugging, or for deploying in an environment where speed isn't an issue. But
if you're trying to hash as many passwords as you can in 10 seconds, it's best
to not turn it on! So there's a good reason to have the option to compile two
different executables, which we called `wrongarg` and `wrongarg.asan` above.

## GDB
Another tool that can help us debug memory errors is one we have been using a little bit already, `gdb`. `gdb` is a command-line debugger that allows us to step through our program line by line and inspect the values of variables at each step. It can also give us backtraces through our program to show us where the error may have occurred.


