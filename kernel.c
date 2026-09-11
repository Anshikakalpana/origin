#include <stdint.h>
#include "port.h"
#include "idt.h"
#include "paging.h"
#include "physical_memory_manager.h"
#include "heap.h"
#include "pit.h"
#include "exceptions.h"

extern struct memory_block *head;
extern volatile uint32_t tick_count;

char *memory = (char*) 0xB8000;
int cursor_row = 0;
int cursor_col = 0;

void new_line(){
    cursor_row++;
    cursor_col = 0;

    if (cursor_row >= 25) {
        cursor_row = 0;
    }
}

void backspace(){
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

void print_number(uint32_t number){
    if (number == 0) {
        print("0");
        return;
    }
    char buffer[11];
    int x = 0;
    while (number > 0) {
        int remainder = number % 10;
        buffer[x] = '0' + remainder;
        number = number / 10;
        x++;
    }
    for (int i = x - 1; i >= 0; i--) {
        char single_char[2] = {buffer[i], '\0'};
        print(single_char);
    }
}

void pic_init() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11); 
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0xFC);  
    outb(0xA1, 0xFF);  
}

/*
void task_one() {
    while (1) {
        print("A");
    }
}

void task_two() {
    while (1) {
        print("B");
    }
}
*/

void kernel_main(void) {
    print("Hello m OS! \n heyy its me");
    print(" This is a test.");

    pic_init();
    interrupt_table_init();
    paging_init();
    pit_init(); 

    /*
    task_init(task_one);
    task_init(task_two);
    start_first_task();
    */

    asm volatile("sti");
volatile int b = 0;
int a = 5;
int result = a / b;
print_number(result);

    print("\nTicks: ");
    print_number(tick_count);

    while (1) { }
}
