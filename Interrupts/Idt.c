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

#include "Idt.h"
#include "../BinaryStructs.h"
#include "../GDT/Gdt.h"
#include "../Utils/LowIo.h"
#include "Pic.h"
#include <stdbool.h>

static bool idt_ready = false;

__attribute__((aligned(0x10)))
static GateDescriptor32 idt[256]; // Create an array of IDT entries; aligned for performance
static IDTR32 idtr;
extern void *asm_isrStubTable[];

/**
 * @brief Sets the descriptor for the given vector.
 *
 * @param vector the vector number
 * @param isr the address of the ISR
 */
static void idtSetDescriptor(int vector, void *isr);

void lockNLoadIDTAndPICs(void) {
	if (idt_ready) {
		return;
	}

	for (int vector = 0; vector < 256; vector++) {
		idtSetDescriptor(vector, asm_isrStubTable[vector]);
	}

	idtr.offset = (uintptr_t) &idt[0];
	idtr.size = 256 * sizeof(GateDescriptor32) - 1;

	__asm__ volatile (
			"lidt    %0"
			:
			: "m" (idtr)
			);

	// This is here to avoid a race condition. Right before the interrupts are enabled, the PICs are remapped.
	initPICs();
	// Disable all IRQs except for the keyboard
	outb(0x21,0xFD);
	outb(0xa1,0xFF);

	__asm__("sti");

	idt_ready = true;
}

static void idtSetDescriptor(int vector, void *isr) {
	GateDescriptor32 *descriptor = &idt[vector];

	descriptor->isr_low        = (uintptr_t) isr & 0xFFFF;
	descriptor->kernel_cs      = getSegDescriptorOffset(&gdt.kernel_code_seg); // this value can be whatever offset your kernel code selector is in your GDT
	descriptor->present	       = 1;
	descriptor->gate_type      = 0xE; // 32-bit interrupt gate
	descriptor->privilege_lvl  = 0;
	descriptor->isr_high       = (uintptr_t) isr >> 16;
}
