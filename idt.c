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
#include "InterruptHandlers.h"
#include "Utils/MemReadWrite.h"
#include <stdbool.h>
#include <stdint.h>

#define PIC1		    0x20 /* IO base address for master PIC */
#define PIC2		    0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA	    (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA	    (PIC2+1)

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr32_t;

static bool idt_ready = false;
__attribute__((aligned(0x10))) //This line wasn't here from the video. Start following the wiki instead, and only check with the video what you have to do and if it's well done.
// https://wiki.osdev.org/Interrupts_tutorial - todo search for (and see what it is) idt_entry_t and idt_desc_t, and rename here to that.
static struct GateDescriptor32 idt[256];

static void encodeIDTEntryOffset(struct GateDescriptor32 *target, uint32_t offset);

void lockNLoadIDT(void) {
	if (idt_ready) {
		printf("IDT already prepared. Aborting...\n");

		return;
	}

	for (int i = 0; i < 256; ++i) {
		encodeIDTEntryOffset(&idt[i], 0);
		idt[i].selector = getSegDescriptorOffset(&gdt.kernel_code_seg);
		idt[i].gate_type = 0xE;
		idt[i].privilege_level = 0;
		idt[i].present = 1;
	}

	// Must be 6 bytes, and I'm starting at position 0 of the 1st byte (easier with inline-asm...).
	idtr32_t idt_info[2];
	idt_info->limit = sizeof(idt) - 1;
	// These are already linear addresses - read what you wrote on the GDT equivalent code.
	idt_info->base |= (uint32_t) &idt;

	// todo https://wiki.osdev.org/PIC#Initialisation, video 55:06+

	__asm__ volatile (
			"lidt    %0"
			:
			: "m" (idt_info)
			);
	__asm__("sti");

	printf("IDT and interrupt flag ready\n");

	idt_ready = true;
}

/**
 * @brief Encode the given offset into the given gate descriptor.
 *
 * @param target the target descriptor
 * @param limit the offset to apply
 */
static void encodeIDTEntryOffset(struct GateDescriptor32 *target, uint32_t offset) {
	writeMem16((uint8_t *) target + (0*2), (uint16_t) offset);
	writeMem16((uint8_t *) target + (3*2), (uint16_t) (offset >> (2*8u)));
}
