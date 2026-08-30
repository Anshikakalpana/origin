#include <stdint.h>
#include "port.h"
#include "idt.h"

char *memory = (char*) 0xB8000;
int cursor_row = 0;
int cursor_col = 0;

void new_line(){
    cursor_row++;
    cursor_col = 0;
}

void clear(){
    if (cursor_col > 0) {
        cursor_col--;
        int index = (cursor_row * 80 + cursor_col) * 2;
        memory[index] = ' ';
        memory[index + 1] = 0x07;
    }
}

void print(char *message) {
    for (int i = 0; message[i] != '\0'; ++i) {

        if(message[i]=='\n' ){
            new_line();
            continue;
        }

        if (cursor_col >= 80) {
            new_line();
        }

        int index = (cursor_row * 80 + cursor_col) * 2;
        memory[index] = message[i];
        memory[index + 1] = 0x07;
        cursor_col++;
    }
}

// initialize the programmable interrupt controller (pic)

// The pic manages interrupt requests from hardware devices
// and forwards them to the cpu

// multiple devices may request the cpu's attention at the same time.
// The pic handles these requests, including masking and priority,
// and delivers the corresponding interrupt to the cpu

// simplified interrupt path:

// keyboard -IRQ1 -> master pic -> cpu
// timer     -IRQ0 -> master pic -> cpu
// disk     -IRQ14 -> slave pic -> master pic -> cpu


void pic_init() {
   
    outb(0x20, 0x11);
    outb(0xA0, 0x11); 

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0xFD);  
    outb(0xA1, 0xFF);  
}

void kernel_main(void) {
    print("Hello m OS! \n heyy its me");
    print(" This is a test.");

    pic_init();
    idt_init();
    asm volatile("sti");

    while (1) { }
}
