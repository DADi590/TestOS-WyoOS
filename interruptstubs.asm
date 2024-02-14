; Copyright 2022 DADi590
;
; Licensed to the Apache Software Foundation (ASF) under one
; or more contributor license agreements.  See the NOTICE file
; distributed with this work for additional information
; regarding copyright ownership.  The ASF licenses this file
; to you under the Apache License, Version 2.0 (the
; "License"); you may not use this file except in compliance
; with the License.  You may obtain a copy of the License at
;
;   http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing,
; software distributed under the License is distributed on an
; "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
; KIND, either express or implied.  See the License for the
; specific language governing permissions and limitations
; under the License.

SECTION .text
	extern interruptHandler
	extern exceptionHandler
	global isrStubTable

	%macro IsrErrStub 1
    isrStub%+%1:
    	mov dword [number], %1
    	push dword [number]
        call exceptionHandler
        add esp, 4 ; remove the pushed number
        iret
    %endmacro
	%macro IsrNoErrStub 1
    isrStub%+%1:
    	mov dword [number], %1
    	push dword [number]
        call exceptionHandler
        add esp, 4 ; remove the pushed number
        iret
    %endmacro

	IsrNoErrStub  0
	IsrNoErrStub  1
	IsrNoErrStub  2
	IsrNoErrStub  3
	IsrNoErrStub  4
	IsrNoErrStub  5
	IsrNoErrStub  6
	IsrNoErrStub  7
	IsrErrStub    8
	IsrNoErrStub  9
	IsrErrStub    10
	IsrErrStub    11
	IsrErrStub    12
	IsrErrStub    13
	IsrErrStub    14
	IsrNoErrStub  15
	IsrNoErrStub  16
	IsrErrStub    17
	IsrNoErrStub  18
	IsrNoErrStub  19
	IsrNoErrStub  20
	IsrNoErrStub  21
	IsrNoErrStub  22
	IsrNoErrStub  23
	IsrNoErrStub  24
	IsrNoErrStub  25
	IsrNoErrStub  26
	IsrNoErrStub  27
	IsrNoErrStub  28
	IsrNoErrStub  29
	IsrErrStub    30
	IsrNoErrStub  31

    isrStubTable:
    %assign i 0
    %rep    32
        dd isrStub%+i ; use DQ instead if targeting 64-bit
    %assign i i+1
    %endrep

SECTION .data
	number:
		dd 0
