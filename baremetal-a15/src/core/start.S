/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

Vectors:
	b	Reset_Handler
	b	.

	.globl   Reset_Handler
Reset_Handler:
	mov		r0, #1
	mov		r1, #2
	mov		r2, #3
	b		.

