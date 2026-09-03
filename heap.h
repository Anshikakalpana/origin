#ifndef HEAP;
define HEAP;

struct memory_bock{
    int size;
    int free;
    struct memory_block *next_memory_block;

}

int malloc();
void free( int address );

#endif;
