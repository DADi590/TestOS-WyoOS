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
struct SegmentSelector {
	unsigned int privilege_level:2;
	unsigned int table_type:1;
	unsigned int index: 13;
} __attribute__((packed, aligned(16)));

/**
 * @brief The Segment Descriptor struct.
 */
struct SegmentDescriptor {
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
} __attribute__((packed));

/**
 * @brief The GDT, as loaded to the processor.
 */
struct GDT {
	struct SegmentDescriptor null_seg_descriptor;
	struct SegmentDescriptor kernel_code_seg;
	struct SegmentDescriptor kernel_data_seg;
	struct SegmentDescriptor task_state_seg;
} __attribute__((packed));

/**
 * @brief The GateDescriptor32 struct.
 */
struct GateDescriptor32 {
	uint16_t offset_1;              // offset bits 0..15
	uint16_t selector;              // a code segment selector in GDT or LDT
	uint8_t  reserved;              // unused, set to 0
	unsigned int gate_type:4;
	unsigned int zero:1;            // unused, set to 0
	unsigned int privilege_level:2;
	unsigned int present:1;
	uint16_t offset_2;               // offset bits 16..31
} __attribute__((packed));



#endif //TESTOS_BINARYSTRUCTS_H
