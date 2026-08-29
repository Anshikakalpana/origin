#include <stdint.h>
#include "port.h"

extern void print(char *message);

void keyboard_handler_main() {
    uint8_t scancode = inb(0x60);
    print("Key pressed!\n");
    outb(0x20, 0x20);
}
