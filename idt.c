#include "idt.h"
#include "isr.h"

struct idt_entry idt[256];

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_ptr idtp;

void idt_set_gate(int n, uint32_t handler) {
    idt[n].address_low = handler & 0xFFFF;
    idt[n].selector = 0x10;
    idt[n].zero = 0;
    idt[n].flags = 0x8E;
    idt[n].address_high = (handler >> 16) & 0xFFFF;
}


void idt_init() {
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0);
    }
    idt_set_gate(33, (uint32_t) keyboard_handler);
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t) &idt;

    asm volatile("lidt %0" : : "m" (idtp));
}