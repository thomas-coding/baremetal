/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

	.section startup, "ax"
	.balign 0x20


	.globl   start
start:
	mov		x0, #1
	mov		x1, #2
	mov		x2, #3
	mov		x3, #4
	mov		x4, #5

	/* Get currnt EL */
	mrs		x0, CurrentEL
	cmp		x0, 0xc
	b.eq	3f
	cmp		x0, 0x8
	b.eq	2f
	cmp		x0, 0x4
	b.eq	1f

/* EL3 now run from this*/
3:
	mov		x1, #3
	b		0f

/* EL2 */
2:
	mov		x1, #2
	b		0f

/* EL1 */
1:
	mov		x1, #1
	b		0f

0:
	mov		x10, #1
	mov		x11, #2
	mov		x12, #3
	mov		x13, #4

	/* Use SP_EL0 at all Exception levels. */
	msr spsel, #0

	/* Setup stack */
	ldr x0, =__stack
	mov sp, x0

	bl	main
	b	.
