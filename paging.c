#include <stdint.h>
#include "paging.h"

// for one page - 4 MB
// uint32_t page_directory[1024] __attribute__((aligned(4096)));
// uint32_t first_page_table[1024] __attribute__((aligned(4096)));

// void paging_init() {
//     for (int i = 0; i < 1024; i++) {
//         first_page_table[i] = (i * 0x1000) | 3;
//     }

//     for (int i = 0; i < 1024; i++) {
//         page_directory[i] = 0 | 2;
//     }

//     page_directory[0] = ((uint32_t) first_page_table) | 3;

//     asm volatile("mov %0, %%cr3" : : "r"(page_directory));

//     uint32_t cr0;
//     asm volatile("mov %%cr0, %0" : "=r"(cr0));
//     cr0 |= 0x80000000;
//     asm volatile("mov %0, %%cr0" : : "r"(cr0));
// }

// for four pages - 16 MB

uint32_t page_directory[1024] __attribute__((aligned(4096)));

uint32_t page_tables[4][1024] __attribute__((aligned(4096)));

void paging_init() {

    for (int directory = 0; directory < 4; directory++) {

        page_directory[directory] = ((uint32_t)page_tables[directory]) | 3;

        for (int table = 0; table < 1024; table++) {

            uint32_t physical_address = (directory * 1024 + table) * 0x1000;

            page_tables[directory][table] = physical_address | 3;
        }
    }

    for (int i = 4; i < 1024; i++) {
        page_directory[i] = 0;
    }

    asm volatile("mov %0, %%cr3" : : "r"(page_directory));

    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));

    cr0 |= 0x80000000;

    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}
