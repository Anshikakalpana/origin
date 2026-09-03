#include "heap.h";

int kmalloc(int size){
    struct memory_block *temp= head;
    struct memory_block *temp= 0;
    while(temp!=0){
    if(temp->free && temp->size>= size){
        temp->free = 0;
        return (int) (temp+1);
    }
    last= temp;
    temp= temp->next;
    
    int new_page= alloc_page();

    if(!new_page ==-1)return -1;

    struct memory_block *new_memory_block= struct (memory_block *) (new_page * 4096);
    new_memory_block->size= 4096-sizeof(memory_block);
    new_memory_block->free = 0;
    new_memory_block->next =0;
    if(head==0){
       head=  new_memory_block;
    }
    else{
        last->next= new_memory_block;

    }
    return (int) (new_memory_block+1);


 }
}