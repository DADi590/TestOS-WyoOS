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

#ifndef TESTOS_LOWIO_H
#define TESTOS_LOWIO_H



#include <stdint.h>

/**
 * @brief Wrapper for the OUT x86 instruction.
 *
 * @param port_addr target port address
 * @param value value to output to the given port
 */
inline void out(uint32_t port_addr, uint32_t value);
/**
 * @brief Wrapper for the IN x86 instruction.
 *
 * @param port_addr target port address
 *
 * @return the value returned by the given port
 */
inline uint32_t in(uint32_t port_addr);

/**
 * @brief Wait 1 to 4 microseconds by outputting 0 to an unused port (0x80).
 */
inline void io_wait(void);



#endif //TESTOS_LOWIO_H
