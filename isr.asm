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
