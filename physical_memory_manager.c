#include <stdint.h>
#include "physical_memory_manager.h"

uint32_t bitmap[32];

int alloc_page() {
    for (int i = 1; i < 1024; i++) {
        int index = i / 32;
        int offset = i % 32;

        int bit_allocated = bitmap[index] & (1 << offset);

        if (bit_allocated) {
            continue;
        }

        bitmap[index] = bitmap[index] | (1 << offset);
        return i;
    }
    return -1;
}

void free_page(int page_number) {
    int index = page_number / 32;
    int offset = page_number % 32;

    bitmap[index] = bitmap[index] & ~(1 << offset);
}
