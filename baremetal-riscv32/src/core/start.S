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
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		exception_test
#	jal		x1, assemble_study
#	jal		csr_study
#	jal		jump_to_m_mode_test
	jal		jump_to_s_mode_test
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

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

exception_test:
	addi	s2, x1, 0 //save lr

	/* Set exception enter address, mode is base */
	la		t0, _vector
	csrw	mtvec, t0

	mret //test for cause exception

	addi	x1, s2, 0 //restore lr
	ret

jump_to_m_mode_test:
	addi	s2, x1, 0 //save lr

	/* Clear mstatus mpp bit[12:11] to 0 */
	li		t0, MSTATUS_MPP_MASK
	csrc    mstatus, t0

	/* Set mstatus mpp bit[12:11] to 11 m mode*/
	li		t0, MSTATUS_MPP_M
	csrs	mstatus, t0

	/* Set mepc to m mode entry */
	la		t0, 1f
	csrw	mepc, t0

	/* Return from m-mode, to mpp(here is m-mode), pc from mepc(here is after 1 label) */
	mret

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
1:
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

	addi	x1, s2, 0 //restore lr
	ret

jump_to_s_mode_test:
	addi	s2, x1, 0 //save lr

	/* Clear mstatus mpp bit[12:11] to 0 */
	li		t0, MSTATUS_MPP_MASK
	csrc    mstatus, t0

	/* Set mstatus mpp bit[12:11] to 11 s mode*/
	li		t0, MSTATUS_MPP_S
	csrs	mstatus, t0

	/* Set mepc to s mode entry */
	la		t0, 2f
	csrw	mepc, t0

	/* Set pmp, enable 0x0000_0000 ~ 0xffff_ffff access by s mode */
	li		t0, 0x3fffffff
	csrw	pmpaddr0, t0
	li		t0, 0xf
	csrw	pmpcfg0, t0

	/* Return from m-mode, to mpp(here is m-mode), pc from mepc(here is after 1 label) */
	mret

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

/* S mode entry */
2:
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

	addi	x1, s2, 0 //restore lr
	ret