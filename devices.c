#include <stdint.h>
#include "port.h"

extern void print(char *message);
extern void clear();

char keys[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};



void keyboard_handler_main() {
   uint8_t key_to_print = inb(0x60);
   if(key_to_print<128){
        if (key_to_print == 14) {
            clear();
        } else {
            char letter = keys[key_to_print];
            char message_to_print[2] = {letter, '\0'};
            print(message_to_print);
        }
    }
    outb(0x20, 0x20);
}


