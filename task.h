// #ifndef TASK
// #define TASK
// #include <stdint.h>

// struct task_manager{
//     uint32_t stack_pointer;
//     struct task_manager *next;
// };

// void take_init(void (*entry_point)());
// void add_task(struct task_manager *new_task);
// void schedule();

// #endif


#ifndef TASK
#define TASK
#include <stdint.h>

struct task_manager{
    uint32_t stack_pointer;
    struct task_manager *next;
};

void task_init(void (*entry_point)());
void add_task(struct task_manager *new_task);
void schedule();
void switch_task();

#endif