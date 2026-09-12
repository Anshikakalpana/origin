#include "task.h"
#include <stdint.h>
#include "heap.h"
#include "pit.h"

// we are implementing circular linked list here se that we can do jobs in a circular method

struct task_manager *current_task=0;
struct task_manager *task_list_head=0;

void add_task(struct task_manager *new_task){
    if(task_list_head==0){
        task_list_head= new_task;
        new_task->next= new_task;
        current_task=  new_task;
    }
    else {
        struct task_manager *temp = task_list_head;
        while(temp->next!=task_list_head){
            temp= temp->next;
        }
        temp->next= new_task;
        new_task->next= task_list_head;

    }
}

extern volatile uint32_t tick_count;

// switch tasks after every 100 ms
void schedule() {
current_task = current_task->next;
}

void task_init(void (*entry_point)()) {
    int stack_memory = kmalloc(4096);

    if (stack_memory == -1) {
        return;
    }

    uint32_t stack_top = stack_memory + 4096;

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // EDI

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // ESI

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // EBP

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // ESP (dummy)

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // EBX

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // EDX

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // ECX

    stack_top -= 4;
    *((uint32_t *) stack_top) = 0;  // EAX

    stack_top -= 4;
    *((uint32_t *) stack_top) = (uint32_t) entry_point;

    struct task_manager *new_task = (struct task_manager *) kmalloc(sizeof(struct task_manager));
    new_task->stack_pointer = stack_top;

    add_task(new_task);
}