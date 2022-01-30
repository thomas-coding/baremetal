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

load_and_store_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		clear_reg // jar equ jal x1, label

	/* SB instruction */
	lui		a0, 0x11223 // set a0 to 0x11223344
	addi	a0, a0, 0x344
	lui		a1, 0x81000 // set a1 to 0x8100_0000, should use riscv32, 64 will spread bit 32-63 to 1, it will be 0xffff_ffff_8100_0000
	sb		a0, 0(a1) // store byte a0[7:0] to a1 + 0, [0x81000000] = 0x55

	addi	x1, s2, 0 //restore lr
	ret

logical_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop

	jal		clear_reg // jar equ jal x1, label

	/* XOR instruction */
	addi	a0, x0, 0b101010
	addi	a1, x0, 0b010101
	xor		a2, a0, a1 // a0 ^ a1, bit by bit , save to a2, a2 = a0 ^ a1

	/* XORI instruction */
	xori	a3, a0, 0b101010 // a0 ^ 0b101010, bit by bit , save to a3, a3 = a0 ^ 0b101010

	/* OR instruction */
	or		a4, a0, a1 // a0 | a1, bit by bit, save to a4, a4 = a0 | a1

	/* ORI instruction */
	ori		a5, a0, 0b101010 // a0 | 0b101010, save to a5, a5 = a0 | 0b101010

	/* AND instruction */
	and		a6, a0, a1 // a0 & a1, save to a6, a6 = a0 & a1

	/* ANDI instruction */
	andi	a7, a0, 0b101010 // a0 & 0b101010, save to a7, a7 = a0 & 0b101010

	addi	x1, s2, 0 //restore lr
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
	jal		logical_instruction
	jal		load_and_store_instruction
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop


	addi	x1, s1, 0 //restore lr
	ret
