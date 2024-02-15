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


%macro SAVE_REGS 0
    pushad
    push ds
    push es
    push fs
    push gs
%endmacro
%macro RESTORE_REGS 0
    pop gs
    pop fs
    pop es
    pop ds
    popad
%endmacro

%macro IsrErrStub 1
isrStub%+%1:
	; Can't use SAVE_REGS and RESTORE_REGS here because the error code is pushed onto the stack
	; todo use SAVE_REGS and RESTORE_REGS and push the error code onto the stack one more time manually
	; (meaning, get the error code from the stack after SAVE_REGS and push it again)
	mov dword [number], %1
	push dword [number]
	call exceptionHandlerErr
	add esp, 8 ; remove the pushed number and the error code
	iret
%endmacro
%macro IsrNoErrStub 1
isrStub%+%1:
	SAVE_REGS
	mov dword [number], %1
	push dword [number]
	call exceptionHandlerNoErr
	add esp, 4 ; remove the pushed number
	RESTORE_REGS
	iret
%endmacro


SECTION .text
	extern interruptIgnore
	extern interruptHandler
	extern exceptionHandlerNoErr
	extern exceptionHandlerErr
	global isrStubTable
	global asm_interruptIgnore

	asm_interruptIgnore:
		SAVE_REGS
		call interruptIgnore
		RESTORE_REGS
		iret

	; Err vs NoErr means that the ISR will push an error code onto the stack vs not pushing
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
