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

//
// Created by Edw590 on 14/02/2024.
//

#ifndef TESTOS_PIC_H
#define TESTOS_PIC_H



#include <stdint.h>

/**
 * @brief Initializes the Programmable Interrupt Controllers (PIC).
 */
void initPICs(void);

/**
 * @brief Sends the End Of Interrupt (EOI) command to the PIC(s).
 *
 * @param irq_num the IRQ number to send the EOI command to
 */
void sendEOI(uint8_t irq_num);



#endif //TESTOS_PIC_H
