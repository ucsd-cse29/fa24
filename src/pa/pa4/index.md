# PA4 – Malloc

In class, quizzes, and PAs we've _used_ `malloc` and `free` to manage memory.
These are functions [written in
C](https://sourceware.org/git/?p=glibc.git;a=blob;f=malloc/malloc.c)! `glibc`
contains one of the [frequently used
implementations](https://sourceware.org/glibc/wiki/MallocInternals).

There are a lot of details that go into these implementations – we don't expect
that anyone could internalize all the details from the documentation above
quickly. However, there are a few key details that are really interesting to
study. In this project, we'll explore how to implement a basic version of
`malloc` and `free` that would be sufficient for many of the programs we have
written.

Specfically, we will practice the following concepts in C:

- bitwise operations,
- pointer arithmetic,
- memory management, and of course,
- using the terminal and vim.


## Task Specification

You will implement two functions.

### `vmalloc`

```c
void *vmalloc(size_t size);
```

The `size_t size` parameter specifies the number of bytes the caller wants.
This has the same meaning as the usual `malloc` we have been using: the returned
pointer is to the start of `size` bytes of memory that is now exclusively
available to the caller.

Note the `void *` return type, whic is the same as the usual `malloc`.  `void *`
is not associatd with any concrete data type. It is used as a generic pointer,
and can be implicitly assigned to any other type of pointer.

This is how `malloc` (and our `vmalloc`) allow assigning the result to any pointer type:

```c
int *p = malloc(sizeof(int) * 10);
char *c = malloc(sizeof(char) * 64);
```

If `size` is not greater than `0`, or if the allocator could not find a heap
block that is large enough for the allocation, then `vmalloc` should return
`NULL` to indicate no allocation was made.

Your implementation of `vmalloc` must:

- Use a “best fit” allocation policy
- Always return an address that is a multiple of 8
- Always allocate space on 8-byte boundaries

More details are in the implementation guide.

### `vmfree`

```c
void vmfree(void* ptr)
```

The `vmfree` function expects a 8-byte aligned address obtained by a previous
call to `vmalloc`. If the address ptr is `NULL`, then vmfree does not perform any
action and returns directly. If the block appears to be a free block, then
`vmfree` does not perform any action and returns.

For allocated blocks, `vmfree` updates the block metadata to indicate that it is
free, and _coalesces_ with adjacent (previous and next) blocks if they are also
free.

More details are in the implementation guide.

## Getting Started

The starter code for this assignment is hosted on GitHub Classroom. Use the
following link to accept the GitHub Classroom assignment:

Just like on PA2/3, clone the repository to ieng6 server.

### The Code Base

Unlike previous PAs, this PA comes with starter code that you should read and understand.

#### The Library

- `vmlib.h`: This header file defines the public interface of our library. Other programs wishing to use our library will include this header file.
- `vm.h`: This header file defines the internal data structures, constants, and helper functions for our memory management system. It is not meant to be exposed to users of the library.
- `vminit.c`: This file implements functions that set up our “heap”.
- `vmalloc.c`: This file implements our own allocation function called `vmalloc`.
- `vmfree.c`: This file implements our own free function called `vmfree`.
- `utils.c`: This file implements helper functions and debug functions.

#### Testing

- `vmtest.c`: This file is not a part of the library. It defines a main function and uses the library functions we created. We can test our library by compiling this file into its own program to run tests. You can write code in the `main()` function here for testing purposes.
- `tests/`: This directory contains small programs and other files which you should use for testing your code. We will explain this in more detail in a later section.

#### Compiling the Starter Code

To compile, run `make` in the terminal from the root directory of the repository. You should see the following items show up in your directory:

- `libvm.so`: This is a dynamically linked library, i.e., our own memory allocation system that can be linked to other programs (e.g., vmtest). The interface for this library is defined in `vmlib.h`. The `Makefile`s handle compiling with a `.so` for you; we set it up this way to match how production systems include libraries like `stdlib`
- `vmtest`: This executable is compiled from vmtest.c with libvm.so linked together. It uses your memory management library to allocate/free memory.
- The starter code in `vmtest.c` is very simple: it calls `vminit()` to initialize our simulated “heap”, and calls the vminfo() function to print out the contents of the heap in a neatly readable format. Run the vmtest executable to find out what the heap looks like rgith after it’s been initialize! (Hint: it’s just one giant free block.)

#### Reading the Starter Code

In this programming assignment, the metadata (header and footer information) is 8 bytes in size, and all blocks are 16-byte aligned. This means the smallest unit of allocation is 16.

The `size_t` data type, which you will see frequently throughout this PA, is a 64-bit (8-byte) unsigned integer type.

Begin by reading through the `vm.h` file, where we define the internal data structures for the heap. This is where you will find the all-important block headers and block footers. Focus on understanding how struct `block_header` is used. You will see it in action later.

Next, open `vminit.c`. This is a very big file containing functions that create and set up the simulated heap for this assignment. Find the `init_heap()` function, and read through the entire thing to understand how it is setting up the heap. There is pointer arithmetic involved, you will need to do similar things for implementing `vmalloc` and `vmfree`, so make sure you have a solid understanding of that. (Why is it necessary to cast pointers to different types?)

Just like production allocators, we create a large chunk of memory as our heap using `mmap`, and allocations/frees are performed in that memory region.

Once you understand what the `init_heap()` function is doing, open up `utils.c`. Here we have implemented the function `vminfo()`, which will be your ally throughout this PA. This function traverses through the heap blocks and prints out the metadata in each block header. You should find inspiration for how to write your own `vmalloc` function here. Look at how it manipulates the pointer to jump between blocks!







