#include <stdint.h>
#include "port.h"

char *memory = (char*) 0xB8000;
int cursor_row = 0;
int cursor_col = 0;

void new_line(){
    cursor_row++;
    cursor_col = 0;
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


void kernel_main(void) {
    print("Hello m OS! \n heyy its me");
    print(" This is a test.");

    while (1) { }
}

// function to initialize pic (programmable interrupt controller)
// in simple words pic is a way for kwyboard to talk with other hardwares
// now the question is how do they actually talk?
// not every device is connected to cpu as it could increase the load on cpu
// keyboard is connected to pic , all the hardwares are connected to pic and pic is connected to cpu
// keyboard -> pic -> cpu


void pic_init() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}