#ifndef TASK
#define TASK

struct task_management{
    uint32_t stack_pointer;
    struct task_management *next;
};

void take_init(void (*entry_point)());

void schedule();

#endif
