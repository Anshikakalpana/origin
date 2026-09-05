global keyboard_handler
extern keyboard_handler_main

keyboard_handler:
    pusha              
    call keyboard_handler_main
    popa               
    iret

global timer_handler
extern timer_handler_main

timer_handler:
    pusha
    call timer_handler_main
    popa
    iret

global switch_task
extern current_task
extern schedule
extern current_task

switch_task:
    pusha

    mov eax, [current_task]
    mov [eax], esp

    call schedule

    mov eax, [current_task]
    mov esp, [eax]

    popa
    ret