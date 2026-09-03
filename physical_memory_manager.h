#ifndef PHYSICAL_MEMORY_MANAGER
#define PHYSICAL_MEMORY_MANAGER

int alloc_page();
void free_page(int page_number);