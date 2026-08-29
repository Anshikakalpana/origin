// idt is a table/array which saves details( what function to run for that particular interrupt) of  every interrupt
// ifndef is a keyword saying if not defined then run the next line which is define


#ifndef IDT
#define IDT

#include <stdint.h>

//this is how information is stored in table/array for that particular interrupt
struct idt_entry {
    // address is of 32 bits but hardware doesnt allow to save 32 bits for an address so we save it in 2 halves, one is lower half( which saves least significant 16 bits ) other is higher( which saves most significant 16 bits )
    uint16_t address_low;
   // a 16-bit field that specifies the index of the code segment in the Global Descriptor Table (GDT) in which the interrupt handler will execute
    uint16_t selector;
    // an 8-bit reserved field that is always set to zero, as required by the x86 architecture specification
    uint8_t  zero;
    uint8_t  flags;
    uint16_t address_high;
} __attribute__((packed));

void idt_init();

#endif
