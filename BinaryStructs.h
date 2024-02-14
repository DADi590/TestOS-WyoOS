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

#ifndef TESTOS_BINARYSTRUCTS_H
#define TESTOS_BINARYSTRUCTS_H



#include <stdint.h>

/**
 * @brief The Segment Selector struct.
 */
typedef struct SegmentSelector {
	unsigned int privilege_level:2;
	unsigned int table_type:1;
	unsigned int index: 13;
} __attribute__((packed, aligned(16))) SegmentSelector;

/**
 * @brief The Segment Descriptor struct.
 */
typedef struct SegmentDescriptor {
	uint16_t limit_1;
	uint16_t base_1;
	uint8_t base_2;

	// Access byte
	unsigned int access:1;
	unsigned int read_write:1;
	unsigned int direction:1;
	unsigned int executable:1;
	unsigned int type:1;
	unsigned int privilege_level:2;
	unsigned int present:1;

	unsigned int limit_2:4;

	// Flags nibble
	unsigned int reserved:1;
	unsigned int long_mode:1;
	unsigned int size:1;
	unsigned int granularity:1;

	uint8_t base_3;
} __attribute__((packed)) SegmentDescriptor;

/**
 * @brief The GDT, as loaded to the processor.
 */
typedef struct GDT {
	SegmentDescriptor null_seg_descriptor;
	SegmentDescriptor kernel_code_seg;
	SegmentDescriptor kernel_data_seg;
	SegmentDescriptor task_state_seg;
} __attribute__((packed)) GDT;

/**
 * @brief The GateDescriptor32 struct.
 */
typedef struct GateDescriptor32 {
	uint16_t isr_low;               // The lower 16 bits of the ISR's address
	uint16_t kernel_cs;             // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t  reserved;              // Set to zero
	unsigned int gate_type:4;
	unsigned int zero:1;
	unsigned int privilege_lvl:2;
	unsigned int present:1;
	uint16_t isr_high;              // The higher 16 bits of the ISR's address
} __attribute__((packed)) GateDescriptor32;

/**
 * @brief The IDTR struct.
 */
typedef struct IDTR32 {
    uint16_t	size;
    uint32_t	offset;
} __attribute__((packed)) IDTR32;



#endif //TESTOS_BINARYSTRUCTS_H
