# PA4 Resubmission – Malloc

_This assignment is thanks to the [staff of CSE29 spring 2024](https://cse29sp24.github.io/docs/instructors.html), especially [Gerald Soosairaj](https://geraldsoosairaj.github.io) and Jerry Yu._

- **Resubmission Due Tuesday, Dec 10, 10pm**
- GitHub Classroom: [https://classroom.github.com/a/ngxgHFB3](https://classroom.github.com/a/ngxgHFB3)

## Resubmission instructions
**If you want to resubmit PA4, please read this section carefully. You need to pass all the tests in the original PA4, while also implementing an extra functionality and answering a new design question described below.**

### `vminfo`

In `utils.c`, we have implemented the function vminfo(), which traverses through the heap blocks and prints out the metadata in each block header.
Update the function so that at the end of its output, it prints details about the largest available block as follows:
```
The largest free block is #x with size y.
```
where `x` is the blockid starting from 0, and `y` is the size (including header) of the largest available block for allocation.
If there are multiple candidates for the largest block, `x` should be the smallest blockid of the candidates.
Refer the following updated output of `vminfo` as an example:
```
vminit: heap created at 0x707df3026000 (4096 bytes).
vminit: heap initialization done.
---------------------------------------
 #      stat    offset   size     prev   
---------------------------------------
 0      BUSY    8        48       BUSY   
 1      FREE    56       32       BUSY   
 2      BUSY    88       112      FREE   
 3      BUSY    200      96       BUSY   
 4      FREE    296      208      BUSY   
 5      BUSY    504      64       FREE   
 6      BUSY    568      320      BUSY   
 7      FREE    888      208      BUSY   
 8      BUSY    1096     160      FREE   
 9      BUSY    1256     368      BUSY   
 10     BUSY    1624     272      BUSY   
 11     FREE    1896     672      BUSY   
 12     BUSY    2568     128      FREE   
 13     BUSY    2696     464      BUSY   
 14     FREE    3160     672      BUSY   
 15     BUSY    3832     160      FREE   
 16     FREE    3992     96       BUSY   
 END    N/A     4088     N/A      N/A    
---------------------------------------
Total: 4080 bytes, Free: 6, Busy: 11, Total: 17
The largest free block is #11 with size 672
```
In this example, there are six `FREE` blocks with the two largest `FREE` blocks being 672 bytes in size: the output line shows the index of the 672 sized block that comes first.

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
- Always return an address that is a multiple of **16**
- Always allocate space on **16-byte** boundaries

More details are in the implementation guide.

### `vmfree`

```c
void vmfree(void* ptr)
```

The `vmfree` function expects a **16-byte** aligned address obtained by a previous
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
  - [Starter Code](./starter-code.md)
  - [Implementation Guide and Milestones](./guide.md)
  - [Testing](./testing.md)
