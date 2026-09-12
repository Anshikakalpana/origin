#include <stdint.h>
#include "port.h"

extern void print(char *message);
extern void backspace();

char keys[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

char command[100];
int command_index=0;

void keyboard_handler_main() {
    uint8_t key_to_print = inb(0x60);
    if (key_to_print < 128) {
        if (key_to_print == 14) {
            backspace();
            if (command_index > 0) {
                command_index--;
            }
        }
        else if (key_to_print == 28) {
            command[command_index] = '\0';
            print("\n");
            print(command);
            print("\n");
            command_index = 0;
        }
        else {
            if (command_index < 99) {
                char letter = keys[key_to_print];
                char command_to_print[2]={letter,'\0'};
                print(command_to_print);
                command[command_index] = letter;
                command_index++;
            }
        }
    }
    outb(0x20, 0x20);
}


