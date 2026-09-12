#include <stdint.h>

extern void print(char *message);
extern char command[];
extern struct task_manager *current_task;
extern void switch_task();
extern volatile uint32_t tick_count;

void system_write(uint32_t string_address) {
    char *message = (char *) string_address;
    print(message);
}

int system_read(char *destination_buffer, int max_length) {
    int i;
    for (i = 0; i < max_length - 1 && command[i] != '\0'; i++) {
        destination_buffer[i] = command[i];
    }
    destination_buffer[i] = '\0';
    return i;
}

void system_exit() {
    while (1) { }
}

int system_getpid() {
    return (int) current_task;
}

void system_yield() {
    switch_task();
}

void system_sleep(int milliseconds) {
    uint32_t target = tick_count + milliseconds;
    while (tick_count < target) { }
}

void system_call_handler_main() {
    uint32_t syscall_number;
    uint32_t arg1;

    asm volatile("mov %%eax, %0" : "=r"(syscall_number));
    asm volatile("mov %%ebx, %0" : "=r"(arg1));

    if (syscall_number == 1) {
        system_write(arg1);
    }
    else if (syscall_number == 2) {
        system_exit();
    }
    else if (syscall_number == 3) {
        system_getpid();
    }
    else if (syscall_number == 4) {
        system_yield();
    }
    else if (syscall_number == 5) {
        system_read((char *) arg1, 100);
    }
    else if (syscall_number == 6) {
        system_sleep(arg1);
    }
}