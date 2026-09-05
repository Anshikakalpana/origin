#include <stdint.h>
#include "timer.h"
#include "port.h"

extern void print(char *message);
extern void print_number(uint32_t num);

volatile uint32_t tick_count = 0;

extern void switch_task();

void timer_handler_main() {
    tick_count++;

    if (tick_count % 1000 == 0) {
        print("\n Seconds: ");
        print_number(tick_count / 1000);
    }

    outb(0x20, 0x20);

    // if (tick_count % 50 == 0) {
    //     switch_task();
    // }
}
