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

#include "Gdt.h"
#include <stdint.h>
#include "CLibs/stdio.h"
#include "Utils/MemReadWrite.h"
#include <stdbool.h>

static void encodeGdtEntryBase(struct SegmentDescriptor *target, uint32_t base);
static void encodeGdtEntryLimit(struct SegmentDescriptor *target, uint32_t limit);
static void setGdtEntryFlags(struct SegmentDescriptor *target, uint8_t flags);

struct GDT gdt = {0};
bool gdt_ready = false;

void lockNLoadGDT(void) {
	if (gdt_ready) {
		printf("GDT already prepared. Aborting...\n");

		return;
	}

	encodeGdtEntryBase(&gdt.kernel_code_seg, 0);
	encodeGdtEntryLimit(&gdt.kernel_code_seg, (64*1024*1024)/4096); // 64 MiB, but in 4 KiB chunks as required by the Granularity.
	writeMem8((uint8_t *) &gdt.kernel_code_seg + 5, 0x9A);
	setGdtEntryFlags(&gdt.kernel_code_seg, 0xC);

	encodeGdtEntryBase(&gdt.kernel_data_seg, 0);
	encodeGdtEntryLimit(&gdt.kernel_data_seg, (64*1024*1024)/4096);
	writeMem8((uint8_t *) &gdt.kernel_data_seg + 5, 0x92);
	setGdtEntryFlags(&gdt.kernel_data_seg, 0xC);

	// Must be 6 bytes, and I'm starting at position 0 of the 1st byte (easier with inline-asm...).
	uint32_t gdt_info[2];
	gdt_info[0] = sizeof(gdt) - 1;
	// "Offset: The linear address of the GDT (not the physical address, paging applies).", OSDev. It's my understanding
	// then, since Viktor just got the address of the variables normally, that the bootloader has already prepared the
	// virtual address space by setting up the processor or something like that, and we no longer have access to the
	// physical addresses, only linear and virtual ones.
	gdt_info[0] |= ((uint32_t) &gdt) << (2*8u);
	gdt_info[1] = ((uint32_t) &gdt) >> (2*8u);

	__asm__ volatile (
			"lgdt    [%0]"
			:
			: "r" (gdt_info)
			);

	printf("GDT ready\n");

	gdt_ready = true;
}

uint16_t getSegDescriptorOffset(struct SegmentDescriptor const *segment_descriptor) {
	// The calculations are made with (uint8_t *) because this way the operations are made byte by byte, and not 2 in 2
	// like it would happen with (uint16_t *).
	return (uint16_t) ((uint8_t const *) segment_descriptor - (uint8_t *) &gdt);
}

/**
 * @brief Encode the given base into the given segment descriptor.
 *
 * @param target the target descriptor
 * @param limit the base to apply
 */
static void encodeGdtEntryBase(struct SegmentDescriptor *target, uint32_t base) {
	writeMem16((uint8_t *) target + (1*2), (uint16_t) base);
	writeMem8((uint8_t *) target + 4, (uint8_t) (base >> (2*8u)));
	writeMem8((uint8_t *) target + 7, (uint8_t) (base >> (3*8u)));
}

/**
 * @brief Encode the given limit into the given segment descriptor.
 *
 * @param target the target descriptor
 * @param limit the limit to apply
 */
static void encodeGdtEntryLimit(struct SegmentDescriptor *target, uint32_t limit) {
	// Check the limit to make sure that it can be encoded
	if (limit > 0xFFFFF) {
		printf("GDT cannot encode limits larger than 0xFFFFF\n");
	}

	// Encode the limit
	writeMem16((uint8_t *) target + (0*2), limit & 0x0000FFFFu);
	writeMem8((uint8_t *) target + 6, readMem8((uint8_t *) target + 6) & 0xF0u); // Clear nibble before ORing
	writeMem8((uint8_t *) target + 6, readMem8((uint8_t *) target + 6) | (uint8_t) (limit >> (2*8u)));
}

/**
 * @brief Set the given flags in the given segment descriptor.
 *
 * @param target the target descriptor
 * @param flags the flags to apply
 */
static void setGdtEntryFlags(struct SegmentDescriptor *target, uint8_t flags) {
	writeMem8((uint8_t *) target + 6, readMem8((uint8_t *) target + 6) & 0x0Fu); // Clear nibble before ORing
	writeMem8((uint8_t *) target + 6, readMem8((uint8_t *) target + 6) | (uint8_t) (flags << 4u));
}
