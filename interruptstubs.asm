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

	%macro isr_err_stub 1
    isr_stub_%+%1:
    	mov dword [number], %1
    	push dword [number]
        call exceptionHandler
        iret
    %endmacro
    %macro isr_no_err_stub 1
    isr_stub_%+%1:
    	mov dword [number], %1
    	push dword [number]
        call interruptHandler
        iret
    %endmacro

	isr_no_err_stub 0
	isr_no_err_stub 1
	isr_no_err_stub 2
	isr_no_err_stub 3
	isr_no_err_stub 4
	isr_no_err_stub 5
	isr_no_err_stub 6
	isr_no_err_stub 7
	isr_err_stub    8
	isr_no_err_stub 9
	isr_err_stub    10
	isr_err_stub    11
	isr_err_stub    12
	isr_err_stub    13
	isr_err_stub    14
	isr_no_err_stub 15
	isr_no_err_stub 16
	isr_err_stub    17
	isr_no_err_stub 18
	isr_no_err_stub 19
	isr_no_err_stub 20
	isr_no_err_stub 21
	isr_no_err_stub 22
	isr_no_err_stub 23
	isr_no_err_stub 24
	isr_no_err_stub 25
	isr_no_err_stub 26
	isr_no_err_stub 27
	isr_no_err_stub 28
	isr_no_err_stub 29
	isr_err_stub    30
	isr_no_err_stub 31

    isrStubTable:
    %assign i 0
    %rep    32
        dd isr_stub_%+i ; use DQ instead if targeting 64-bit
    %assign i i+1
    %endrep

SECTION .data
	number:
		dd 0
