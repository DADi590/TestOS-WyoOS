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

#ifndef TESTOS_MEMREADWRITE_H
#define TESTOS_MEMREADWRITE_H



#include <stdint.h>

void writeMem64(void *addr, uint64_t data);
void writeMem32(void *addr, uint32_t data);
void writeMem16(void *addr, uint16_t data);
void writeMem8(void *addr, uint8_t data);
void writeMem64i(uint32_t addr, uint64_t data);
void writeMem32i(uint32_t addr, uint32_t data);
void writeMem16i(uint32_t addr, uint16_t data);
void writeMem8i(uint32_t addr, uint8_t data);
uint64_t readMem64(void const *addr);
uint32_t readMem32(void const *addr);
uint16_t readMem16(void const *addr);
uint8_t readMem8(void const *addr);
uint64_t readMem64i(uint32_t addr);
uint32_t readMem32i(uint32_t addr);
uint16_t readMem16i(uint32_t addr);
uint8_t readMem8i(uint32_t addr);



#endif //TESTOS_MEMREADWRITE_H
