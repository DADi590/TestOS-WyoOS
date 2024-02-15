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

#include "LowIo.h"

void outb(uint16_t port_addr, uint8_t value) {
	__asm__ volatile (
			"out     %0, %1;"
			:
			: "Nd" (port_addr), "a" (value)
			: "memory"
			);
}
void outw(uint16_t port_addr, uint16_t value) {
	__asm__ volatile (
			"out     %0, %1;"
			:
			: "Nd" (port_addr), "a" (value)
			: "memory"
			);
}
void outl(uint16_t port_addr, uint32_t value) {
	__asm__ volatile (
			"out     %0, %1;"
			:
			: "Nd" (port_addr), "a" (value)
			: "memory"
			);
}

uint8_t inb(uint32_t port_addr) {
	uint8_t value = 0;
	__asm__ volatile (
			"in      %0, %1;"
			: "=a" (value)
			: "Nd" (port_addr)
			);

	return value;
}
uint16_t inw(uint32_t port_addr) {
	uint16_t value = 0;
	__asm__ volatile (
			"in      %0, %1;"
			: "=a" (value)
			: "Nd" (port_addr)
			);

	return value;
}
uint32_t inl(uint32_t port_addr) {
	uint32_t value = 0;
	__asm__ volatile (
			"in      %0, %1;"
			: "=a" (value)
			: "Nd" (port_addr)
			);

	return value;
}

void io_wait(void) {
	outb(0x80, 0);
}
