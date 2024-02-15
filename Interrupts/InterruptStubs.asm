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

IRQ_BASE EQU 32

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
%macro IntHandler 1
isrStub%+%1:
	SAVE_REGS
	mov dword [number], %1 - IRQ_BASE
	push dword [number]
	call interruptHandler
	add esp, 4 ; remove the pushed number
	RESTORE_REGS
	iret
%endmacro


SECTION .text
	extern interruptHandler
	extern exceptionHandlerNoErr
	extern exceptionHandlerErr
	global asm_isrStubTable

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

	; This infinity is just for me to be able to return the number of the interrupt
	IntHandler 32
    IntHandler 33
    IntHandler 34
    IntHandler 35
    IntHandler 36
    IntHandler 37
    IntHandler 38
    IntHandler 39
    IntHandler 40
    IntHandler 41
    IntHandler 42
    IntHandler 43
    IntHandler 44
    IntHandler 45
    IntHandler 46
    IntHandler 47
    IntHandler 48
    IntHandler 49
    IntHandler 50
    IntHandler 51
    IntHandler 52
    IntHandler 53
    IntHandler 54
    IntHandler 55
    IntHandler 56
    IntHandler 57
    IntHandler 58
    IntHandler 59
    IntHandler 60
    IntHandler 61
    IntHandler 62
    IntHandler 63
    IntHandler 64
    IntHandler 65
    IntHandler 66
    IntHandler 67
    IntHandler 68
    IntHandler 69
    IntHandler 70
    IntHandler 71
    IntHandler 72
    IntHandler 73
    IntHandler 74
    IntHandler 75
    IntHandler 76
    IntHandler 77
    IntHandler 78
    IntHandler 79
    IntHandler 80
    IntHandler 81
    IntHandler 82
    IntHandler 83
    IntHandler 84
    IntHandler 85
    IntHandler 86
    IntHandler 87
    IntHandler 88
    IntHandler 89
    IntHandler 90
    IntHandler 91
    IntHandler 92
    IntHandler 93
    IntHandler 94
    IntHandler 95
    IntHandler 96
    IntHandler 97
    IntHandler 98
    IntHandler 99
    IntHandler 100
    IntHandler 101
    IntHandler 102
    IntHandler 103
    IntHandler 104
    IntHandler 105
    IntHandler 106
    IntHandler 107
    IntHandler 108
    IntHandler 109
    IntHandler 110
    IntHandler 111
    IntHandler 112
    IntHandler 113
    IntHandler 114
    IntHandler 115
    IntHandler 116
    IntHandler 117
    IntHandler 118
    IntHandler 119
    IntHandler 120
    IntHandler 121
    IntHandler 122
    IntHandler 123
    IntHandler 124
    IntHandler 125
    IntHandler 126
    IntHandler 127
    IntHandler 128
    IntHandler 129
    IntHandler 130
    IntHandler 131
    IntHandler 132
    IntHandler 133
    IntHandler 134
    IntHandler 135
    IntHandler 136
    IntHandler 137
    IntHandler 138
    IntHandler 139
    IntHandler 140
    IntHandler 141
    IntHandler 142
    IntHandler 143
    IntHandler 144
    IntHandler 145
    IntHandler 146
    IntHandler 147
    IntHandler 148
    IntHandler 149
    IntHandler 150
    IntHandler 151
    IntHandler 152
    IntHandler 153
    IntHandler 154
    IntHandler 155
    IntHandler 156
    IntHandler 157
    IntHandler 158
    IntHandler 159
    IntHandler 160
    IntHandler 161
    IntHandler 162
    IntHandler 163
    IntHandler 164
    IntHandler 165
    IntHandler 166
    IntHandler 167
    IntHandler 168
    IntHandler 169
    IntHandler 170
    IntHandler 171
    IntHandler 172
    IntHandler 173
    IntHandler 174
    IntHandler 175
    IntHandler 176
    IntHandler 177
    IntHandler 178
    IntHandler 179
    IntHandler 180
    IntHandler 181
    IntHandler 182
    IntHandler 183
    IntHandler 184
    IntHandler 185
    IntHandler 186
    IntHandler 187
    IntHandler 188
    IntHandler 189
    IntHandler 190
    IntHandler 191
    IntHandler 192
    IntHandler 193
    IntHandler 194
    IntHandler 195
    IntHandler 196
    IntHandler 197
    IntHandler 198
    IntHandler 199
    IntHandler 200
    IntHandler 201
    IntHandler 202
    IntHandler 203
    IntHandler 204
    IntHandler 205
    IntHandler 206
    IntHandler 207
    IntHandler 208
    IntHandler 209
    IntHandler 210
    IntHandler 211
    IntHandler 212
    IntHandler 213
    IntHandler 214
    IntHandler 215
    IntHandler 216
    IntHandler 217
    IntHandler 218
    IntHandler 219
    IntHandler 220
    IntHandler 221
    IntHandler 222
    IntHandler 223
    IntHandler 224
    IntHandler 225
    IntHandler 226
    IntHandler 227
    IntHandler 228
    IntHandler 229
    IntHandler 230
    IntHandler 231
    IntHandler 232
    IntHandler 233
    IntHandler 234
    IntHandler 235
    IntHandler 236
    IntHandler 237
    IntHandler 238
    IntHandler 239
    IntHandler 240
    IntHandler 241
    IntHandler 242
    IntHandler 243
    IntHandler 244
    IntHandler 245
    IntHandler 246
    IntHandler 247
    IntHandler 248
    IntHandler 249
    IntHandler 250
    IntHandler 251
    IntHandler 252
    IntHandler 253
    IntHandler 254
    IntHandler 255
    IntHandler 256

    asm_isrStubTable:
    %assign i 0
    %rep    256
        dd isrStub%+i
    %assign i i+1
    %endrep

SECTION .data
	number:
		dd 0
