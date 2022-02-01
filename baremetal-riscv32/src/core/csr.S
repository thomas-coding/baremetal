/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

clear_reg_for_csr:

	addi	a0,	x0, 0 //Set a0 to 0
	addi	a1, x0, 0
	addi	a2, x0, 0
	addi	a3, x0, 0
	addi	a4, x0, 0
	addi	a5, x0, 0
	addi	a6, x0, 0
	addi	a7, x0, 0

	ret


csr_instruction:
	addi	s2, x1, 0 //save lr

	/* Write csr */
#	CSRRW	x0, csr, rs1 // CSRW csr, rs1
#	CSRRWI	x0, csr, zimm //CSRWI csr, zimm

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		clear_reg_for_csr // jar equ jal x1, label

	/* 0x4014112d, bit[31:30] = 01, RV32 mode; bit18 = 1, support supervisor mode; bit20 = 1, support user mode */
	csrrs	a0, misa, x0

	/* 0, hart id, core0, we can add QEMU option "-smp 2", then this code will called twice, and wtih different core id */
	csrrs	a1, mhartid, x0

	/* 0, 
	 * bit3 MIE machine mode interrupt enable, 0 - interrupt disabled
	 */
	csrrs	a2, mstatus, x0

	/* 0, 
	 * Machine Trap-Vector Base-Address Register
	 */
	csrrs	a3, mtvec, x0

	/* 0 */
	csrrs	a4, mcause, x0

	addi	x1, s2, 0 //restore lr
	jalr x0, 0(x1) //jump to x1(witch is lr, so return), equ instruction ret
	
/* Use qemu + gdb, check instruction behvior */
.globl csr_study
csr_study:
	addi	s1, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		csr_instruction
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop


	addi	x1, s1, 0 //restore lr
	ret
