// Copyright 2022 DADi590
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "GDT/Gdt.h"
#include "CLibs/stdio.h"
#include "Interrupts/Idt.h"
#include <stdbool.h>
#include <stdnoreturn.h>

/*
 * ALLOWED C STANDARD LIBRARIES TO USE (because of freestanding environment)
 * <float.h>
 * <limits.h>
 * <stdarg.h>
 * <stddef.h>
 * <iso646.h>
 * <stdbool.h>
 * <stdint.h>
 * <stdalign.h>
 * <stdnoreturn.h>
 * This is up to date with up to the C17 standard (checked in 2022-10-14).
 */

noreturn void kernelNoExit(void);

/**
 * @brief The Kernel's main function.
 *
 * @param multiboot_struct the multiboot struct given by the bootloader
 * @param magic_number the multiboot magic number given by the bootloader
 */
noreturn void kernelMain(__attribute__((unused)) void const *multiboot_struct,
                         __attribute__((unused)) uint32_t magic_number) {
	// todo GRUB also provides a memory map, whatever that is - go see about it.

	resetScreen();
	printf("TestOS\n\n");

	// For randomizing stack tests
	//unsigned int a,b,c,d;
	//__asm__ volatile ("cpuid" : "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (0x00));
	//printf("CPUID: %u %u %u %u\n", a, b, c, d);

	printf("Initializing GDT...\n");
	lockNLoadGDT();

	printf("Initializing IDT and PICs...\n");
	lockNLoadIDTAndPICs();



	kernelNoExit();
}

noreturn void kernelNoExit(void) {
	printf("\nWhile true...\n-------------------------\n");
	while (true) {
		// So that the kernel doesn't stop
	}
}
