#include "gdt.h"
#include "CFuncs/stdio.h"
#include <stdbool.h>
#include <stdint-gcc.h>

void kernelMain(void const *multiboot_struct, uint32_t magic_number) {
	printS("Hello, World!\n");

	prepareGDT();

	printS("\nWhile true...");
	while (true) {
		// So that the kernel doesn't stop
	}
}
