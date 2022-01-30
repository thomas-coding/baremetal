/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

clear_reg:

	addi	a0,	x0, 0 //Set a0 to 0
	addi	a1, x0, 0
	addi	a2, x0, 0
	addi	a3, x0, 0
	addi	a4, x0, 0
	addi	a5, x0, 0
	addi	a6, x0, 0
	addi	a7, x0, 0

	ret

calc_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

	jal		clear_reg // jar equ jal x1, label

	/* ADDI instruction */
	addi	a0, x0, 0x555 //add 0 and 0x555, save to a0, a0 = 0 + 0x555

	/* ADD instruction */
	add		a1, a0, a0 //add a0 and a0, save to a1, a1 = a0 + a0

	/* SUB instruction */
	addi	a2, x0, 0x444
	sub		a3, a0, a2 //sub a0 and a2, save to a3, a3 = a0 - a2

	/* LUI instruction */
	lui		a4, 0x999	// 0x999 << 12, save to a4, low bit set to 0, a4 = 0x999000

	/* AUIPC instrucion */
	auipc	a5, 0x10	//add pc and 0x10 << 12, save to a5, a5 = pc + (0x10 << 12)

	addi	x1, s2, 0 //restore lr
	jalr x0, 0(x1) //jump to x1(witch is lr, so return), equ instruction ret
	
/* Use qemu + gdb, check instruction behvior */
.globl assemble_study
assemble_study:
	addi	s1, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		x1, calc_instruction
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop


	addi	x1, s1, 0 //restore lr
	ret
