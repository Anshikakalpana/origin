#include <stdint.h>
#include "exceptions.h"

extern void print(char *message);

void exception_handler_main(int exception_number){
    if (exception_number == 0){
        print("exception: divide by zero\n");
    }
    else if(exception_number == 4){
        print("exception: overflow\n");
    }
    else if(exception_number == 5){
        print("exception: bound range exceed\n");
    }
    else if(exception_number == 6){
        print("exception: invalid opcode\n");
    }
    else if(exception_number == 13){
        print("exception: general protection fault\n");
    }
    else if(exception_number == 14){
        print("exception: page fault\n");
    }

    while (1) { }
}
