#include <stdint.h>
#include "port.h"
#include "pit.h"

int frequency = 1000;

void pit_init(){
    uint16_t divisor = 1193182 / frequency;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}
