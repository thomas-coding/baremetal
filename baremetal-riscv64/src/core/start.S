/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

.section .text.start

#define MSTATUS_MPP_MASK (3L << 11) // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)

	.globl _start
	.type _start, "function"
_start:
	/* Set exception enter address, mode is base */
	la		t0, _vector
	csrw	mtvec, t0

	/* Init stack and jump to main */
	la		sp, __StackTop
	jal		main

	addi	x0, x0, 0 //nop
	j		.

.align 2
_vector:
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	csrr	t0, mcause
	csrr	t1, mtval
	csrr	t2, mepc

	addi	t3, t2, 4
	csrw	mepc, t3

	mret