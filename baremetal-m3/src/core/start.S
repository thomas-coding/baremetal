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
Assemble_learn:
	push	{r0-r7}						/* Save registers to stack , thumbe only support r0-r7*/
	add     r7, sp, #0					/* Save sp to r7 */

	mov		r0, #0
	mov		r1, #0
	mov		r2, #0
	mov		r3, #0
	mov		r4, #0
	mov		r5, #0
	mov		r6, #0

	mov		sp, r7						/* Restore sp*/
	pop		{r0-r7}						/* Restore registers*/
	bx		lr							/* Return*/

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


