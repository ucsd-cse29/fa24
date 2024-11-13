# PA4 – Malloc

- **Due Monday, Nov 25, 10pm**
- Github Classroom: [https://classroom.github.com/a/ngxgHFB3](https://classroom.github.com/a/ngxgHFB3)

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

You will implement and test two functions.

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

## Design Questions

_Heap fragmentation_ occurs when there are many available blocks that are
small-sized and not adjacent (so they cannot be coalesced).

1. Give an example of a program (in C or pseudocode) that sets up a situation
where a 20-byte `vmalloc` call **fails** to allocate despite the heap having (in
total) over 200 bytes free across many blocks. Assume all the policies and
layout of the allocator from the PA are used (best fit, alignment, coalescing
rules, and so on)

2. Give an example of a program (in C or pseudocode) where all the allocations
succeed if using the _best fit_ allocation policy (like in this PA), but some
allocations would fail due to fragmentation if the _first fit_ allocation policy
was used instead, keeping everything else the same.

## Submission

You'll submit on Gradescope as usual. Refer to the [policies on
collaboration](https://ucsd-cse29.github.io/fa24/#policies) if you need to
refresh your memory.

We will compile your program using the provided `Makefile`s, which you should
not change.

To get started read through the next few sections about the PA:
  - [Starter Code](./pa/pa4/starter-code.md)
  - [Implementation Guide and Milestones](./pa/pa4/guide.md)
  - [Testing](./pa/pa4/testing.md)
