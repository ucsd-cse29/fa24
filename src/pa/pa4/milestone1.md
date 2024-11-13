# Implementation Guide

This provides detailed implementation information and a suggested workflow.

## Incremental Development Tips

- Run the starter code and understand the output. Always figure out how to run your program first! You can’t do any testing if you don’t know how to run your program.
- Understand the `init_heap()` function.
- Understand the `vminfo()` function.
- Begin writing the `vmalloc()` function:
  - write and test the size calculation code.
  - write and test the best-fit policy. (A helper function would be great here.) See later section for testing images.
  - write and test splitting free blocks.
Begin writing the vmfree() function:
- Update `vmalloc()` implementation to include block footers.
- write and test a basic `vmfree()` implementation that only frees one block.
- write and test coalescing with the previous/next block.
- Test everything!

Consider some helper functions along the way:

- A function to get the size of a block in bytes given a pointer to the beginning of it
- A function to get the size of a block in 8-byte words given a pointer to the beginning of it
- A function for getting a pointer to the _next_ block given a pointer to the beginning of a block

## Implementing `vmalloc`

### Allocation Size Calculation

We need to do some calculations based on the requested size to get the actual block size that we need to look for in our heap.

- Add 8 bytes for the block header to the requested size;
- Round up the new size to the nearest multiple of 16.

For example, if the user calls `vmalloc(10)`, we first add 8 bytes for the header to get 18, and then round up to the nearest multiple of 16, which gets us 32. So to allocate 10 bytes, we need to look for a heap block that is _at least_ 32 bytes in size.

### Allocation Policy

Many allocation _policies_ are possible – choosing the first block that fits, choosing the last block that fits, choosing the most-recently-freed block that fits, and so on. The one you **must** implement for this PA is the best-fit policy.

That is, once you have determined the size requirement of the desired heap block, you need to traverse the entire heap to find the best-fitting block – the smallest block that is large enough to fit the allocation. If there are multiple candidates of the same size, then you should use the first one you find.

### Splitting Large Blocks

If the best-fitting block you find is larger than what we need, then we need to split that block into two. For example, if we are looking for a 16-byte block for vmalloc(4), and the best fitting candidate is a 64-byte block, then we will split it into a 16-byte block and a 48-byte block. The former is allocated and returned to the caller, the latter remains free.

### Updating Block Header(s)

If a new block was created as a result of a split, you need to create a new header for it, and

- set the correct size.
- set the status bit to 0.
- set the previous bit to 1.

And for the block that was allocated, you need to

- update the size (if splitting happened).
- set the status bit to 1.
- go to the next block header (if it’s not the end mark) and set its previous bit to 1.

### Returning the Address

After updating all the relevant metadata, vmalloc should return a pointer to the start of the payload. Do not return the address of the block header!

## Implementing vmfree

To free a block, the following actions must be taken (not necessarily in this order):

- unset the status bit to 0,
- create a block footer,
- unset the next block’s previous bit,
- coalesce with the next block if it is also free, and
- coalesce with the previous block if it is also free.

If you are coalescing two blocks, remember to update both the header and the footer!

You will also need to revisit your `vmalloc` implementation to add code for creating footers once.

