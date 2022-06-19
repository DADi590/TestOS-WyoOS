#include "port.h"

void out(uint32_t port_addr, uint32_t value) {
	__asm__(
			"out     %0, %1;"
			:
			: "d" (port_addr), "a" (value)
			);
}

uint32_t in(uint32_t port_addr) {
	uint32_t value = 0;
	__asm__(
			"in      %0, %1;"
			: "=a" (value)
			: "d" (port_addr)
			);

	return value;
}
