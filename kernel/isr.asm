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

; exception handling

global exception0_handler
extern exception_handler_main

exception0_handler:
    pusha
    push dword 0
    call exception_handler_main
    add esp, 4
    popa
    iret

global exception4_handler

exception4_handler:
    pusha
    push dword 4
    call exception_handler_main
    add esp, 4
    popa
    iret

global exception5_handler

exception5_handler:
    pusha
    push dword 5
    call exception_handler_main
    add esp, 4
    popa
    iret

global exception6_handler

exception6_handler:
    pusha
    push dword 6
    call exception_handler_main
    add esp, 4
    popa
    iret

global exception13_handler

exception13_handler:
    pusha
    push dword 13
    call exception_handler_main
    add esp, 4
    popa
    iret

global exception14_handler

exception14_handler:
    pusha
    push dword 14
    call exception_handler_main
    add esp, 4
    popa
    iret

; system call handling
global system_call_handler
extern system_call_handler_main

system_call_handler:
    pusha
    call system_call_handler_main
    popa
    iret
