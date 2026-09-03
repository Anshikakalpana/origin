#ifndef HEAP
#define HEAP

struct memory_block{
    int size;
    int free;
    struct memory_block *next;

};

int kmalloc();
void kfree( int address );

#endif
