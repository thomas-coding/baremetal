/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__Vectors:
	.long		__StackTop				/*     Top of Stack */
	.long		Reset_Handler			/*     Reset Handler */
	.long		0x11111111		
	.long		0x22222222		

	.thumb_func
	.globl   Reset_Handler
Reset_Handler:
	mov		r0, #0
	mov		r1, #1
	mov		r2, #2
	mov		r3, #3
	mov		r4, #4
	mov		r5, #5
	mov		r6, #6
	mov		r7, #7
	bl		Assemble_learn
	mov		r7, #6
	bl		main
	mov		r3, #4
	b		.
	mov		r2, #4


