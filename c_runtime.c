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

#include "CLibs/stdio.h"
#include "Utils/KernelUtils.h"
#include "Utils/MemReadWrite.h"

void __stack_chk_fail_local(void) {
	uint32_t esp = 0;
	const uint32_t MAX_ADDRS = 10;

	printf("\nSTACK ATTACK DETECTED. Stacktrace for %u addresses:\n", MAX_ADDRS);

	__asm__ volatile (
			"mov    [%0], esp"
			: "=m" (esp)
			:
			);

	for (uint32_t i = 0; i < MAX_ADDRS; ++i, ++esp) {
		printf("%u: %u\n", esp, 0 != esp ? readMem32i(esp) : 0);
	}

	kernelPanic();
}
