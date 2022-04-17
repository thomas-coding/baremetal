
/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Ref: DUI0552A_cortex_m3_dgug.pdf, Chapter 3 The Cortex-M3 Instruction Set*/
/* Ref: The Definitive Guide to the ARM® Cortex-M3,  Instruction Sets */

#define Test_Memory_Start 0x200000 (2M offset)

/* 
 * total: sram 0x0 - 0x400000 (0-4M)
 *
 * 0x0 - 0x??  text,data,bss
 * blank
 * 0x3e0000 - 0x400000 stack
 */

	.thumb_func
Clear_r0_2_r6:
	push	{lr}
	mov		r0, #0
	mov		r1, #0
	mov		r2, #0
	mov		r3, #0
	mov		r4, #0
	mov		r5, #0
	mov		r6, #0
	pop		{pc}

	/* mov, str, ldr, push, pop */
	.thumb_func
Move_Data:
	push	{r0-r7, lr}
	add		r7, sp, #0

	/* Move form register to register */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	mov		r0, #0xff					/* Move immediate data to register, limit to 0xff, r0 = 0xff */
	mov		r1, r0						/* Move register to register, r1 = r0 */
	movt	r3, #0xff					/* Move immediate data to register top half word , r3 = 0x00ff0000 */
	movw	r4, #0xa5a5					/* Move immediate data to register, limit to 0xffff, r0 = 0xffff */

	/* Move between register and memory */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0x20000000				/* Set r0 to test memory address 0x20000000 */
	mov		r1, #0xff					/* Set r1 to 0xff */
	str		r1, [r0]					/* Store r1 value to address memory 0x20000000(r0) , use gdb command 'x/16xw 0x20000000' to check*/
	ldr		r2, [r0]					/* Load memory 0x20000000 content to r2 */
	ldr		r1, =0x12345678				/* Set r1 = 0x12345678 */
	str		r1, [r0, #0x4]				/* Set 0x20000000 + 0x4 = r1 */

	mov		r1, r0						/* Set r1 to memory base 0x200000 */
	ldr		r2, =0x11
	ldr		r3, =0x22
	ldr		r4, =0x33
	ldr		r5, =0x44
	stm		r1!, {r2-r5}				/* Store r2,r3,r4,r5 to 0x200000, 0x200004, 0x200008, 0x20000c, default is Increase After, and finally set r1 to 0x200010*/
	ldr		r2, =0x0
	ldr		r3, =0x0
	ldr		r4, =0x0
	ldr		r5, =0x0
	mov		r1, r0						/* Set r1 to memory base 0x200000 */
	ldm		r1!, {r2-r5}				/* Load 0x200000, 0x200004, 0x200008, 0x20000c to r2,r3,r4,r5, default is Increase After, and finally set r1 to 0x200010*/

	/* Move between register and stack */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r2, =0x11
	ldr		r3, =0x22
	push	{r2-r3}						/* Origin sp = 0x3fffc0
										 * sp = sp - 4, sp = 0x3fffbc, push r3 to sp(0x3fffbc)
										 * sp = sp - 4, sp = 0x3fffb8, push r2 to sp(0x3fffb8)
										 */

	pop		{r4-r5}						/* Origin sp = 0x3fffb8
										 * sp = 0x3fffb8, pop sp(0x3fffb8) to r4, sp = sp + 4
										 * sp = 0x3fffbc, pop sp(0x3fffbc) to r5, sp = sp + 4
										 * Finally, sp = 0x3fffc0
										 */

	mov		sp, r7
	pop		{r0-r7, pc}


	.thumb_func
Process_Data:
	push	{r0-r7, lr}
 
	/* add, sub, mul, div */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	add		r0, r0, #0x88				/* Add, r0 = r0 + 0x88 */
	ldr		r0, =0x12345678
	ldr		r1, =0x11111111
	add		r2, r0, r1					/* Add, r2 = r0 + r1 */
	sub		r2, r0, r1					/* Sub, r2 = r0 - r1 */
	sub		r2, #0x67					/* Sub, r2 = r2 - 0x67 */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =8
	ldr		r1, =9
	mul		r0, r1						/* Mul, r0 = r0 * r1 */
	ldr		r0, =48
	ldr		r1, =6
	udiv	r2, r0, r1					/* Unsigned div, r2 = r0 / r1 */

	/* and, orr, bic, lsl, lsr */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0b1111
	ldr		r1, =0b0101
	and		r0, r1						/* bitwise and r0 = r0 & r1 */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0b1111
	ldr		r1, =0b0101
	orr		r0, r1						/* bitwise or r0 = r0 | r1 */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0b11111111
	ldr		r1, =0b00110000
	bic		r0, r1						/* bit clear r0 = r0 & (~r1) =0b1100 1111 */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0b00001100
	lsl		r0, #0x3					/* logic shift left r0 = r0 << 0x3 =0b0110 0000 */
	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0b00001100
	lsr		r0, #0x2					/* logic shift right r0 = r0 >> 0x2 =0b0000 0011 */

	pop		{r0-r7, pc}

	.thumb_func
Branch_Test_No_Return:
#	push	{r0-r7, lr}
	ldr		r6, =0xa5a5a5a5
	b		.
#	pop		{r0-r7, pc}

	.thumb_func
Branch_Test_With_Return:
	push	{lr}
	ldr		r6, =0x5a5a5a5a
	pop		{pc}

	.thumb_func
Call_And_Branch:
	push	{r0-r7, lr}

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, = 0x1111
	b		1f							/* branch to 1 (after), so r0 will be still 0x1111 */
	ldr		r0, = 0x2222
1:
	nop

#	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
#	ldr		r0, = Branch_Test_No_Return
#	bx		r0							/* branch to r0 address, not return, if test, open it */

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	bl		Branch_Test_With_Return		/* branch to function with lr saved */

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, = Branch_Test_With_Return
	blx		r0							/* branch to r0 address with lr save */

	pop		{r0-r7, pc}


	.thumb_func
Compare_And_Branch:
	push	{r0-r7, lr}

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0x12121212
	ldr		r1, =0x12121212
	cmp		r0, r1
	beq		2f							/* if r0 = r1, branch to lable 2 */
	ldr		r2, =0x33333333
2:
	ldr		r3, =0x22222222
	nop

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	ldr		r0, =0x12121212
	ldr		r1, =0x12121212
	cmp		r0, r1
	bne		3f							/* if r0 != r1, branch to lable 3 */
	ldr		r2, =0x33333333
3:
	ldr		r3, =0x22222222
	nop

	bl		Clear_r0_2_r6				/* For test, first clear r0-r6 */
	mov		r0, #100					/* Just like C 'for' function, Set loop counter */
loop:
	cbz		r0, loopexit				/* Counter !=0 */
	add		r1, r0
	sub		r0, #1						/* Counter-- */
	b		loop
loopexit:

	dsb									/* Data synchronization barrier */
	isb									/* Instruction synchronization barrierc */

	pop		{r0-r7, pc}


	.thumb_func
	.globl   Assemble_learn
Assemble_learn:
	push	{r0-r7, lr}					/* Save registers to stack , thumbe only support r0-r7 */
	add     r7, sp, #0					/* Save sp to r7 */

	bl		Move_Data					/* Learn data move instruction */
	bl		Process_Data				/* Learn data process instruction */
	bl		Call_And_Branch				/* Learn call and branch instruction */
	bl		Call_And_Branch				/* Learn call and branch instruction */
	bl		Compare_And_Branch			/* Learn compare and branch instructioin */

	mov		sp, r7						/* Restore sp */
	pop		{r0-r7, pc}					/* Restore registers */
