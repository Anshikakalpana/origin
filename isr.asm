global keyboard_handler
extern keyboard_handler_main

keyboard_handler:
    pusha              
    call keyboard_handler_main
    popa               
    iret
