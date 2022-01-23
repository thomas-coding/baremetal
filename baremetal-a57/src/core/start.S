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

	/* Copy .data from flash to sram */
	/* Read copy table, copy form r1 to r2, length is r3 */
	ldr		x0, = __copy_table_start__
	ldr		x1, [x0]
	ldr		x2, [x0, #8]
	ldr		x3, [x0, #16]

	/* r3-4, if result < 0, branch to done */
.L_loop0_0:
	subs	x3, x3, #8
	blt		.L_loop0_0_done
	ldr		x0, [x1, x3]
	str		x0, [x2, x3]
	b		.L_loop0_0
.L_loop0_0_done:

	/* Clear bss */
	/* Read zero table, zero form r0, length is r2 */
	ldr		x0, = __zero_table_start__
	ldr		x1, [x0]
	ldr		x2, [x0, #8]
	/* The value of r0 will fill bss, for test, we can set it to 0xa5a5a5a5 */
	ldr		x0, =0

	/* r2-4, if result < 0, branch to done */
.L_loop0_1:
	subs	x2, x2, #8
	blt		.L_loop0_1_done
	str		x0, [x1, x2]
	b		.L_loop0_1
.L_loop0_1_done:

	bl	main
	b	.
