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

#ifndef TESTOS_STDIO_H
#define TESTOS_STDIO_H



#include <stdint.h>

/**
 * @brief Prints a character on the screen and advanced the last printed position.
 *
 * @param c the character to print
 */
void printC(char c);
/**
 * @brief Read the official printf documentation, this works like the standard one, except it doesn't offer all
 * conversions.
 *
 * To know which conversions are accepted, check the function code.
 */
int printf(char const *fmt_str, ...) __attribute__ ((format(printf, 1, 2)));
/**
 * @brief Prints an unsigned integer of at most 32 bits to the screen.
 *
 * @param num the number to print
 */
int printN32u(uint32_t num);
/**
 * @brief Resets the VGA state to empty and the cursor X and Y positions to 0.
 */
void resetScreen(void);
/**
 * @brief Erases the last printed character.
 */
void eraseChar(void);



#endif //TESTOS_STDIO_H
