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
#include "BinaryStructs.h"
#include "CLibs/stdio.h"
#include "Gdt.h"
#include "Utils/General.h"
#include <stdbool.h>

static bool idt_ready = false;

__attribute__((aligned(0x10)))
static GateDescriptor32 idt[256]; // Create an array of IDT entries; aligned for performance
static IDTR32 idtr;
extern void *isrStubTable[];
extern funcptr_t(asm_interruptIgnore);

/**
 * @brief Sets the descriptor for the given vector.
 *
 * @param vector the vector number
 * @param isr the address of the ISR
 */
static void idtSetDescriptor(int vector, void *isr);

void lockNLoadIDT(void) {
	if (idt_ready) {
		return;
	}

	for (int vector = 0; vector < 32; vector++) {
		idtSetDescriptor(vector, isrStubTable[vector]);
	}
	for (int vector = 32; vector < 256; vector++) {
		idtSetDescriptor(vector, &asm_interruptIgnore);
	}

	idtr.offset = (uintptr_t) &idt[0];
	idtr.size = 256 * sizeof(GateDescriptor32) - 1;

	__asm__ volatile (
			"lidt    %0"
			:
			: "m" (idtr)
			);
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
