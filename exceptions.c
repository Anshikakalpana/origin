#include <stdint.h>
#include "exceptions.h"

extern void print(char *message);

void exception_handler_main(int exception_number){
    if (exception_number == 0) {
        print("EXCEPTION: Divide by Zero\n");
    }

    while (1) { }
}
