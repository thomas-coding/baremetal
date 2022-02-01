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
	jal		x1, assemble_study
	jal		csr_study
	jal		jump_to_m_mode_test
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	j		.


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