// ifndef is a keyword saying if not defined then run the next line which is define

#ifndef PORT_H
#define PORT_H

#include <stdint.h>

// outb with 2 parameters port(where we want to move data) and data
void outb(uint16_t port, uint8_t data);

// inb with 1 parameter port(from where we have to access data)
uint8_t inb(uint16_t port);

#endif