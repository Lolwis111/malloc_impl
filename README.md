# malloc_impl
This is an implementation of a basic memory allocator for PotatOS.

This implementation provides the commonly used functions malloc(), calloc(), realloc() and free().

This implementation is not intended to be used with Unix or Linux and therefor does not use brk()/sbrk() to get more memory from the operating system.
It is intended to be used with PotatOS. To still be able to test it on my Linux machine i implemented the init_c_malloc() function, which gets
some memory from the "real" malloc() function and then we use that allocated memory as a fake heap.
Once it gets implemented in PotatOS this function will have to be replaced with respective syscalls to the PotatOS kernel.

This is also the reason why my functions have the c_ prefix as not to be confused with the c library functions.

