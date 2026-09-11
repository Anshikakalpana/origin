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

switch_task:
    pusha
    mov eax, [current_task]
    mov [eax], esp
    call schedule
    mov eax, [current_task]
    mov esp, [eax]
    popa
    ret

global start_first_task

start_first_task:
    mov eax, [current_task]
    mov esp, [eax]
    popa
    ret

global exception0_handler
extern exception_handler_main

exception0_handler:
    pusha
    push dword 0
    call exception_handler_main
    add esp, 4
    popa
    iret