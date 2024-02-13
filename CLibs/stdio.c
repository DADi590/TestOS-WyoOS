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

#include "stdio.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

#define MAX_64BIT_NUM_LEN 20

enum ScreenProps {
	HORIZ_CHARS = 80,
	VERTICAL_CHARS = 25,
};

static uint16_t * const VIDEO_MEM_ADDR = (uint16_t *) 0xB8000;
static uint8_t curr_cursor_x = 0;
static uint8_t curr_cursor_y = 0;

/**
 * @brief Checks and acts according to the given character, if it's a control character.
 *
 * @param c the character to check
 *
 * @return true if it's a control character, false otherwise
 */
static bool processCtrlChar(char c) {
	if ('\n' == c) {
		curr_cursor_x = 0;
		++curr_cursor_y;

		return true;
	}
	if ('\r' == c) {
		curr_cursor_x = 0;

		return true;
	}

	return false;
}

void printC(char c) {
	uint16_t offset_print = (80 * curr_cursor_y) + curr_cursor_x;

	if (processCtrlChar(c)) {
		return;
	}

	VIDEO_MEM_ADDR[offset_print] = (VIDEO_MEM_ADDR[offset_print] & 0xFF00u) | c;
	++curr_cursor_x;
	if (curr_cursor_x >= 80) {
		curr_cursor_x = 0;
		++curr_cursor_y;
	}
}

int printf(char const *fmt_str, ...) {
	int num_printed_chars = 0;
	va_list args_list;

	va_start(args_list, fmt_str);

	for (size_t i = 0; '\0' != fmt_str[i]; ++i) {
		if ('%' == fmt_str[i]) {
			switch (fmt_str[++i]) {
				case 's': {
					const char *str = va_arg(args_list, char *);
					for (int j = 0; '\0' != str[j]; ++j, ++num_printed_chars) {
						printC(str[j]);
					}

					break;
				}
				case 'c': {
					printC(va_arg(args_list, int));
					++num_printed_chars;

					break;
				}
				case 'u': {
					num_printed_chars += printN32u(va_arg(args_list, unsigned int));

					break;
				}
				default: {
					printC(fmt_str[i]);
					++num_printed_chars;

					break;
				}
			}
		} else {
			printC(fmt_str[i]);
			++num_printed_chars;
		}
	}

	va_end(args_list);

	return num_printed_chars;
}

int printN32(int32_t num) {
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

	return num_digits;
}

int printN32u(uint32_t num) {
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

	return num_digits;
}

void resetScreen(void) {
	curr_cursor_x = 0;
	curr_cursor_y = 0;
	for (size_t i = 0; i < (HORIZ_CHARS * VERTICAL_CHARS); ++i) {
		printC(' ');
	}
	curr_cursor_x = 0;
	curr_cursor_y = 0;
}
