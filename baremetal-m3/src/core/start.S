/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__Vectors:
	.long		__StackTop				/*     Top of Stack */
	.long		Reset_Handler		/*     Reset Handler */
	.long		0x11111111		
	.long		0x22222222		

	.thumb_func
	.globl   Reset_Handler
Reset_Handler:
	mov		r0, #1
	mov		r1, #2
	mov		r2, #3
	mov		r7, #6
	bl		main
	mov		r3, #4
	b		.
	mov		r2, #4
