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

#include "Keyboard.h"
#include "../../Utils/LowIo.h"
#include "../../CLibs/stdio.h"

void keyboardInterruptHandler(void) {
	// https://www.millisecond.com/support/docs/current/html/language/scancodes.htm
	uint8_t scancode = inb(0x60);

	switch (scancode) {
		case 0x02: printf("1"); break;
		case 0x03: printf("2"); break;
		case 0x04: printf("3"); break;
		case 0x05: printf("4"); break;
		case 0x06: printf("5"); break;
		case 0x07: printf("6"); break;
		case 0x08: printf("7"); break;
		case 0x09: printf("8"); break;
		case 0x0A: printf("9"); break;
		case 0x0B: printf("0"); break;

		case 0x10: printf("q"); break;
		case 0x11: printf("w"); break;
		case 0x12: printf("e"); break;
		case 0x13: printf("r"); break;
		case 0x14: printf("t"); break;
		case 0x15: printf("z"); break;
		case 0x16: printf("u"); break;
		case 0x17: printf("i"); break;
		case 0x18: printf("o"); break;
		case 0x19: printf("p"); break;

		case 0x1E: printf("a"); break;
		case 0x1F: printf("s"); break;
		case 0x20: printf("d"); break;
		case 0x21: printf("f"); break;
		case 0x22: printf("g"); break;
		case 0x23: printf("h"); break;
		case 0x24: printf("j"); break;
		case 0x25: printf("k"); break;
		case 0x26: printf("l"); break;

		case 0x2C: printf("y"); break;
		case 0x2D: printf("x"); break;
		case 0x2E: printf("c"); break;
		case 0x2F: printf("v"); break;
		case 0x30: printf("b"); break;
		case 0x31: printf("n"); break;
		case 0x32: printf("m"); break;
		case 0x33: printf(","); break;
		case 0x34: printf("."); break;
		case 0x35: printf("-"); break;

		case 0x1C: printf("\n"); break;
		case 0x39: printf(" "); break;
		case 0x0E: eraseChar(); break;
		default:
			break;
	}
}
