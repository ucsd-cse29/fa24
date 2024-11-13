# Testing


For this PA we provide you with some local testing code to help you make sure your program is working; you will need to write more thorough tests than what we've provided! But we give you a big start

## Test Programs

In the repository, you will find the `tests/` directory, where we have privided some small testing programs that test your library function.

By cding in to the `tests/` directory and running make, you can compile all these test programs and run them yourself. These programs are what we will be using in the autograder as well.

For example, here’s the code for the very first test: `alloc_basic.c`:

```c
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "vmlib.h"
#include "vm.h"

/*
 * Simplest vmalloc test.
 * Makes one allocation and confirms that it returns a valid pointer,
 * and the allocation takes place at the beginning of the heap.
 */
int main()
{
    vminit(1024);

    void *ptr = vmalloc(8);
    struct block_header *hdr = (struct block_header *)
                               ((char *)ptr - sizeof(struct block_header));

    // check that vmalloc succeeded.
    assert(ptr != NULL);
    // check pointer is aligned.
    assert((uint64_t)ptr % 16 == 0);
    // check position of malloc'd block.
    assert((char *)ptr - (char *)heapstart == sizeof(struct block_header));
    // check block header has the correct contents.
    assert(hdr->size_status == 19);

    vmdestroy();
    return 0;
}
```

In this test, we simply make one `vmalloc()` call, and we verify that the allocation returned a valid pointer at the correct location in the heap.

These tests use the `assert()` statement to check certain test conditions. If your code passes the tests, then nothing will be printed. If one of the assert statements fail, then you will see an error.

## Test Images

When you are writing vmalloc, you may wonder how you can test the allocation policy fully when you don’t have the ability to free blocks to create a more realistic allocation scenarios (i.e., a heap with many different allocated/free blocks to search through).

To help you with that, we have created some images in the starter code in the tests/img directory. In your test programs, instead of calling `vminit()`, you can call the `vmload()` function instead to load one of these images.

Our `alloc_basic2` program uses one such image. If you open `tests/alloc_basic2.c`, you will see that it creates the simulated heap using the following function call:

```c
vmload("img/many_free.img");
```

If you load this image and call `vminfo()`, you can see exactly how this image is laid out:

```
vmload: heap created at 0x7c2abd1da000 (4096 bytes).
vmload: heap initialization done.
---------------------------------------
 #      stat    offset   size     prev   
---------------------------------------
 0      BUSY    8        48       BUSY   
 1      BUSY    56       48       BUSY   
 2      FREE    104      48       BUSY   
 3      BUSY    152      32       FREE   
 4      FREE    184      32       BUSY   
 5      BUSY    216      48       FREE   
 6      FREE    264      128      BUSY   
 7      BUSY    392      112      FREE   
 8      BUSY    504      32       BUSY   
 9      FREE    536      112      BUSY   
 10     BUSY    648      352      FREE   
 11     BUSY    1000     304      BUSY   
 12     BUSY    1304     336      BUSY   
 13     FREE    1640     320      BUSY   
 14     BUSY    1960     288      FREE   
 15     BUSY    2248     448      BUSY   
 16     BUSY    2696     256      BUSY   
 17     BUSY    2952     96       BUSY   
 18     BUSY    3048     368      BUSY   
 19     FREE    3416     672      BUSY   
 END    N/A     4088     N/A      N/A    
---------------------------------------
Total: 4080 bytes, Free: 6, Busy: 14, Total: 20
```

You can use this image to test allocating in a more realistic heap.

Three images exist in total:

- `last_free.img`: the last block is free,
- `many_free.img`: many blocks are free,
- `no_free.img`: no block is free (use this to test allocation failure).
