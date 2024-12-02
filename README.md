# malloc_impl
This is an implementation of a basic memory allocator for PotatOS.

This implementation provides the commonly used functions malloc(), calloc(), realloc() and free().

This implementation is not intended to be used with Unix or Linux and therefor does not use brk()/sbrk() to get more memory from the operating system.
It is intended to be used with PotatOS. To still be able to test it on my Linux machine i implemented the init_c_malloc() function, which gets
some memory from the "real" malloc() function and then we use that allocated memory as a fake heap.
Once it gets implemented in PotatOS this function will have to be replaced with respective syscalls to the PotatOS kernel.

This is also the reason why my functions have the c_ prefix as not to be confused with the c library functions.

## Memory layout

The heap starts as one big block.
At the beginning of this block we place a 40 bytes of meta data structure (MEMORY_BLOCK_T).
Each block contains a pointer to the next and last block, to the actual data area, its size and wether or not it is free.

## c_malloc()

Allocation will hangle through the next pointers until one block of sufficient size is found.
If block is bigger than the requested size it is split and the pointer to the data area is returned.
If the block is exactly the requested size we don't have to split and can just return a pointer to the data area.

If no block can be found a NULL pointer is returned. Requesting zero bytes will also return a NULL pointer.

## c_free()

Freeing will try to find the block which this pointer points too.
If the pointer was not returned by any of the allocation functions or does not point to an existing block this function will do nothing.

Once the block is found it will be marked as free. Then the function will try to merge with the previous block and
then automatically merge any two adjacent free blocks.

## c_calloc()

Calloc simply calls malloc and memsets the data area to all zeros ( ideally we wouldn't memset, because we actually write into every byte this might cause page faults and page generation in the kernel which makes this call potentially very expensive. I think the linux kernel avoids this via mmap() which guarantees zero fill without having to actually write into every single byte first... But PotatOS does not have such function [at least not yet]).
 
## c_realloc()

Realloc will first try to merge with the block pointed to by next. If the next block is free and big enough, realloc will merge the given block with the next block.

If the resulting block is bigger than the requested size it is split again into a block of the requested and size and a free block.

If merging with the next block is not possible, either because its too small or simply not free, a new block will be allocated using malloc and then all the data is copied over.
In this case the old block is automatically freed.