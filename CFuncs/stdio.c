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

#include <stdbool.h>
#include "stdio.h"

#define MAX_64BIT_NUM_LEN 20

uint16_t * const video_memory_addr = (uint16_t *) 0xB8000;
uint8_t last_prt_x = 0;
uint8_t last_prt_y = 0;

void printC(char c) {
	uint16_t offset_print = (80 * last_prt_y) + last_prt_x;

	if ('\n' == c) {
		last_prt_x = 0;
		++last_prt_y;

		return;
	}

	video_memory_addr[offset_print] = (video_memory_addr[offset_print] & 0xFF00) | c;
	++last_prt_x;
	if (last_prt_x >= 80) {
		last_prt_x = 0;
		++last_prt_y;
	}
}

void printS(char const *str) {
	for (uint32_t i = 0; '\0' != str[i]; ++i) {
		printC(str[i]);
	}
}

void printNu(uint32_t num) {
	bool stop = false;
	char digits[MAX_64BIT_NUM_LEN] = {0};
	int num_digits = 0;

	for (int i = (MAX_64BIT_NUM_LEN - 1); !stop; --i) {
		digits[i] = (num % 10) + '0';
		num /= 10;
		if (0 == num) {
			stop = true;
		}
		++num_digits;
	}
	for (int i = 0; i < num_digits; ++i) {
		printC(digits[(MAX_64BIT_NUM_LEN - num_digits) + i]);
	}
}
