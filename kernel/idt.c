#include "idt.h"
#include "isr.h"
#include "timer.h"
#include "exceptions.h"
#include "system_call.h"

//in the classic x86 protected-mode/32-bit interrupt architecture, there are 256 possible interrupt vectors
// so we make an array (interrupt_table_entry) of size 256
struct interrupt_table_entry idt[256];

struct interrupt_table_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct interrupt_table_ptr idtp;

void interrupt_table_set_gate(int n, uint32_t handler) {
    idt[n].address_low = handler & 0xFFFF;
    idt[n].selector = 0x10;
    idt[n].zero = 0;
    idt[n].flags = 0x8E;
    idt[n].address_high = (handler >> 16) & 0xFFFF;
}


void interrupt_table_init() {
    for (int i = 0; i < 256; i++) {
        interrupt_table_set_gate(i, 0);
    }
    interrupt_table_set_gate(0x80, (uint32_t) system_call_handler);
    interrupt_table_set_gate(0, (uint32_t) exception0_handler);
    interrupt_table_set_gate(4, (uint32_t) exception4_handler);
    interrupt_table_set_gate(5, (uint32_t) exception5_handler); 
    interrupt_table_set_gate(6, (uint32_t) exception6_handler);
    interrupt_table_set_gate(13, (uint32_t) exception13_handler);
    interrupt_table_set_gate(14, (uint32_t) exception14_handler); 
    interrupt_table_set_gate(32, (uint32_t) timer_handler);
    interrupt_table_set_gate(33, (uint32_t) keyboard_handler);
    idtp.limit = (sizeof(struct interrupt_table_entry) * 256) - 1;
    idtp.base = (uint32_t) &idt;

    asm volatile("lidt %0" : : "m" (idtp));
}
