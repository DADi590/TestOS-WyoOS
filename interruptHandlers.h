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

#ifndef TESTOS_INTERRUPTHANDLERS_H
#define TESTOS_INTERRUPTHANDLERS_H



#include <stdint.h>

/**
 * @brief Handle processor interrupts
 *
 * @param int_num number of interruption
 * @param esp the current ESP (Stack Pointer) value
 *
 * @return the 'esp' parameter
 */
uint32_t interruptHandler(__attribute__((unused)) uint8_t int_num, uint32_t esp);



#endif //TESTOS_INTERRUPTHANDLERS_H
