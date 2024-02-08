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

#include "InterruptHandlers.h"
#include <stdint.h>
#include "CLibs/stdio.h"

uint8_t interrupt_number = 0;

__asm__("intHandlerWrapper:\n"
		"push    ds\n"
		"push    es\n"
		"push    fs\n"
		"push    gs\n"
		"pusha\n"
		"\n"
		"push    esp\n"
		"push    interrupt_number\n"
		"call    interruptHandler\n"
		// No need to clean up the stack, since we're setting ESP to a new value here.
		"mov     esp, eax\n"
		"\n"
		"popa\n"
		"pop    gs\n"
		"pop    fs\n"
		"pop    es\n"
		"pop    ds\n"
		"iret\n"); // IRET must be used here: https://wiki.osdev.org/Interrupt_Service_Routines

uint32_t interruptHandler(uint8_t int_num, uint32_t esp) {
	printf("INTERRUPT %u\n", int_num);

	return esp;
}
