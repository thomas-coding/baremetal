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

control_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		clear_reg // jar equ jal x1, label

	addi	a0, x0, 0x123
	addi	a1, x0, 0x123
	addi	a2, x0, 0x234

	/* BEQ instruction */
	beq		a0, a1, 1f // if a0 = a1, then branch to after lable(offset) 1
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
1:
	addi	x0, x0, 0 //nop

	/* BNE instruction */
	bne		a0, a2, 2f // if a0 != a1, then branch to after lable(offset) 2
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
2:
	addi	x0, x0, 0 //nop

	/* BLT BLTU instruction */
	blt		a0, a2, 3f // if a0 < a2, then branch to after lable(offset) 3
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
3:
	addi	x0, x0, 0 //nop

	/* BGT BGTU instruction */
	bgt		a2, a0, 4f // if a2 > a0, then branch to after lable(offset) 4
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
4:
	addi	x0, x0, 0 //nop


	addi	x1, s2, 0 //restore lr
	ret


compare_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		clear_reg // jar equ jal x1, label

	/* SLT instruction */
	addi	a0, x0, 0x345;
	addi	a1, x0, 0x456;
	slt		a2, a0, a1 // if a0 < a1, then set a2 to 1, a2 = boolean(a0 < a1)

	/* SLTI instruction */
	slti	a3, a0, 0x346 // if a0 < 346, then set a3 to 1, a3 = boolean(a0 < 0x346)

	/* SLTU instruction */
	sltu	a4, a0, a1 // if a0 < a1, then set a4 to 1, unsign compare

	/* SLTIU instruction */
	sltiu	a5, a0, 0x346 // if a0 < 346, then set a5 to 1, unsign compare

	addi	x1, s2, 0 //restore lr
	ret


shift_instruction:
	addi	s2, x1, 0 //save lr

	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		clear_reg // jar equ jal x1, label

	/* SLL instruction */
	addi	a0, x0, 0x1
	addi	a1, x0, 0x7
	sll		a2, a1, a0 // get a0 low 5 bits, a1 << a0, put result to a2, a2 = a1 << a0

	/* SLLI instruction */
	slli	a3, a1, 0x2 // a1 << 2, save to a3, a3 = a1 << 2

	/* SLR instruction */
	srl		a4, a1, a0 // a1 >> a0, save to a4, a4 = a1 >> a1

	/* SLRI instruction */
	srli	a5, a1, 0x2 // a1 >> 2, save to a5, a5 = a1 >> 2

	addi	x1, s2, 0 //restore lr
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
	sb		a0, 0(a1) // store byte a0[7:0] to a1 + 0, [0x81000000] = 0x44

	/* SH instruction */
	sh		a0, 4(a1) // store half word a0[15:0] to a1 + 4, [0x81000004] = 0x3344

	/* SW instruction */
	sw		a0, 8(a1) // store word a0[31:0] to a1 + 8, [0x81000008] = 0x11223344

	/* LD instruction */
	lb		a2, 8(a1) // load byte (a1 + 8)[7:0] to a2, high bit sign extend, a2 = 0x0000_0044

	/* LH instruction */
	lh		a3, 8(a1) // load half word (a1 + 8)[15:0] to a3, high bit sign extend, a3 = 0x0000_3344

	/* LW instruction */
	lw		a4, 8(a1) // load word (a1 + 8)[31:0] to a4, high bit sign extend, a3 = 0x1122_3344

	/* LBU instruction */
	lbu		a5, 8(a1) // load byte unsigned (a1 + 8)[7:0] to a5, high bit extend 0, a5 = 0x0000_0044

	/* LHU instruction */
	lhu		a6, 8(a1) // load half word unsigned (a1 + 8)[15:0] to a6, high bit extend 0, a6 = 0x0000_3344

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

test_label:
	nop
	nop
	ret


calc_instruction:
	addi	s2, x1, 0 //save lr


	rdinstret t0
	nop
	call	test_label
	nop
	rdinstret t1

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
	jal		shift_instruction
	jal		compare_instruction
	jal		control_instruction
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop


	addi	x1, s1, 0 //restore lr
	ret
