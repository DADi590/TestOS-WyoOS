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

#include "MemReadWrite.h"

// These functions are in accordance with strict aliasing rules of the C standard (they always do everything with
// char*, or equivalently, uint8_t*). Copied from the F1DP project.

static inline void writeMem(uint8_t *addr, uint64_t data, uint64_t n_bytes) {
	uint32_t i = 0;
	if (0 == addr) {
		return;
	}

	for (i = 0; i <= (n_bytes - 1); ++i) {
		*(addr+i) = (uint8_t) (data >> (i*8u));
	}
}
void writeMem64(void *addr, uint64_t data) {
	writeMem(addr, data, sizeof(uint64_t));
}
void writeMem32(void *addr, uint32_t data) {
	writeMem(addr, data, sizeof(uint32_t));
}
void writeMem16(void *addr, uint16_t data) {
	writeMem(addr, data, sizeof(uint16_t));
}
void writeMem8(void *addr, uint8_t data) {
	writeMem(addr, data, sizeof(uint8_t));
}

void writeMem64i(uint32_t addr, uint64_t data) {
	writeMem64((void *) addr, data);
}
void writeMem32i(uint32_t addr, uint32_t data) {
	writeMem32((void *) addr, data);
}
void writeMem16i(uint32_t addr, uint16_t data) {
	writeMem16((void *) addr, data);
}
void writeMem8i(uint32_t addr, uint8_t data) {
	writeMem8((void *) addr, data);
}

static inline uint64_t readMem(uint8_t const *addr, uint64_t n_bytes) {
	uint32_t ret_var = 0;
	uint32_t i = 0;
	if (0 == addr) {
		return ret_var;
	}

	for (i = 0; i <= (n_bytes - 1); ++i) {
		ret_var |= ((uint32_t) *addr) << (i*8);
	}

	return ret_var;
}
uint64_t readMem64(void const *addr) {
	return readMem(addr, sizeof(uint64_t));
}
uint32_t readMem32(void const *addr) {
	return (uint32_t) readMem(addr, sizeof(uint32_t));
}
uint16_t readMem16(void const *addr) {
	return (uint16_t) readMem(addr, sizeof(uint16_t));
}
uint8_t readMem8(void const *addr) {
	return (uint8_t) readMem(addr, sizeof(uint8_t));
}

uint64_t readMem64i(uint32_t addr) {
	return readMem64((void const *) addr);
}
uint32_t readMem32i(uint32_t addr) {
	return readMem32((void const *) addr);
}
uint16_t readMem16i(uint32_t addr) {
	return readMem16((void const *) addr);
}
uint8_t readMem8i(uint32_t addr) {
	return readMem8((void const *) addr);
}
