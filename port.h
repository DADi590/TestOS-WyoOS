#ifndef TESTOS_PORT_H
#define TESTOS_PORT_H



#include <stdint-gcc.h>

void out(uint32_t port_addr, uint32_t value);
uint32_t in(uint32_t port_addr);



#endif //TESTOS_PORT_H
