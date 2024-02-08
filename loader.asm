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

; Check the Multiboot specification (v0.6.96) to know what this below means.
ALIGN_INFO EQU 1 << 0
MEM_INFO EQU 1 << 1
VIDEO_INFO EQU 1 << 2
IMG_INFO_BITS EQU 0 << 16
H_MAGIC EQU 0x1BADB002
H_FLAGS EQU (ALIGN_INFO | MEM_INFO)
H_CHECKSUM EQU -(H_MAGIC + H_FLAGS)

H_HEADER_ADDR EQU 0
H_LOAD_ADDR EQU 0
H_LOAD_END_ADDR EQU 0
H_BSS_END_ADDR EQU 0
H_ENTRY_ADDR EQU 0

H_MODE_TYPE EQU 0
H_WIDTH EQU 0
H_HEIGHT EQU 0
H_DEPTH EQU 0

SECTION .multiboot
		align 4
		dd H_MAGIC
		dd H_FLAGS
		dd H_CHECKSUM
		dd H_HEADER_ADDR
		dd H_LOAD_ADDR
		dd H_LOAD_END_ADDR
		dd H_BSS_END_ADDR
		dd H_ENTRY_ADDR
		dd H_MODE_TYPE
		dd H_WIDTH
		dd H_HEIGHT
		dd H_DEPTH

SECTION .rodata
	RET_KERNEL db "Returned from kernel - wtf?", 0
	RET_KERNEL1 db "Coiso: %u", 0Ah, 0

SECTION .bss
		align 16
	stack_bottom:
		resb 2*1024*1024 ; 2 MiB. Must be multiple of 16 (1024 is, so just leave those 2 there and multiply by whatever)
	stack_top:
		dummy_byte db 0 ; If I don't put this here, GCC will put stack_top out of the segment, in another segment (???)

SECTION .text
		extern kernelMain
		extern printf
		global _start

	_start:
		; Set up the stack
		lea     esp, [dummy_byte]

		; Call the main Kernel function with the parameters Multiboot gives
		push    eax
		push    ebx
		call    kernelMain
		add     esp, 2*4

		; Warn in case we returned from the kernel
		lea     eax, [RET_KERNEL]
		push    eax
		call    printf
		add     esp, 1*4

		; Another infinite loop just in case the kernel would leave and return here
		cli
	stop:
		hlt
		jmp     stop
