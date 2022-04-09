
/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Ref: DUI0552A_cortex_m3_dgug.pdf, Chapter 3 The Cortex-M3 Instruction Set*/
/* Ref: The Definitive Guide to the ARM® Cortex-M3,  Instruction Sets */


	.thumb_func
Change_to_privileged:
	push	{r0-r7, lr}

	ldr		r0, =0x0					/* we want set control for change it back to privileged mode */
	msr		control, r0
	isb

	bl		Check_Status				/* Check status, we still at handle mode(11 SVCall) and privileged, use MSP */
	
	pop		{r0-r7, pc}

/* SVC
 100 -- change to privileged
 */
	.globl   SVC_Handler
	.thumb_func
	.syntax unified						/* For TT, need this */
SVC_Handler:
	tst		lr, #0x4					/* Test EXC_RETURN number in LR bit 2 */
	ite		eq							/* If zero (equal) then */
	mrseq	r0, MSP						/* Main Stack was used, put MSP in R0 */
	mrsne	r0, PSP						/* Process Stack was used, put PSP in R0 */

	ldr		r1, [r0, #24]				/* Get stacked PC from stack (PC is next instruction of svc) */
	ldrb	r0, [r1, #-2]				/* Get svc number from the instruction */

	push	{r4-r11, lr}				/* exception r0-r3, if you know which is used in this func, then you should not destory */

svc_handler_1:
	cmp		r0, #100
	bne		svc_handler_2
	bl		Change_to_privileged
	b		svc_handler_end
	
svc_handler_2:

svc_handler_end:

	pop		{r4-r11, pc}


/*
IPSR isr_number bit0-bit8
	0 = Thread mode
	1 = Reserved
	2 = NMI
	3 = HardFault
	4 = MemManage
	5 = BusFault
	6 = UsageFault
	7-10 = Reserved
	11 = SVCall
	12 = Reserved for Debug
	13 = Reserved
	14 = PendSV
	15 = SysTick
	16 = IRQ0

Control register
	bit0: 0 = Privileged 1 = Unprivileged
	bit1: 0 = MSP is the current stack pointer , 1 = PSP is the current stack pointer.
*/
	.thumb_func
Check_Status:
	push	{r0-r7, lr}

	mrs		r0, ipsr					/* 0 - thread mode */
	mrs		r1, control					/* 00 - privileged and msp  */

	pop		{r0-r7, pc}


/* At starting, in thread mode, privileged state. 
 Test change to unprivileged
 Test use svc change to handler mode, privileged state
 Test in svc handler, change back privileged state through control register
 */
	.thumb_func
Privileged_test:
	push	{r0-r7, lr}

	bl		Check_Status				/* Check status, at starting, thread mode and privileged, use MSP */

	ldr		r0, =0x1					/* Change to thread mode and unprivileged, use MSP */
	msr		control, r0
	isb

	bl		Check_Status				/* Check status, at starting, thread mode and unprivileged, use MSP, 
											go on will UsageFault_Handler because of access SCB,
											So we need set return to privileged mode */

	ldr		r0, =0x0					/* we want set control for change it back to privileged mode, but it will fail */
	msr		control, r0
	isb

	bl		Check_Status				/* Check status, we still at thread mode and unprivileged, use MSP */

	svc		#100						/* So we call svc, and in SVC_Handler, we change it to privileged mode */	

	bl		Check_Status				/* Check status, we still at thread mode and unprivileged, use MSP */	

	pop		{r0-r7, pc}


/* Stacking 32 bytes
 R0–R3, R12, LR, PC, and PSR 
 */
	.thumb_func
Exception_stacking_test:
	push	{r0-r7, lr}

	ldr		r0, =0x11111111
	ldr		r1, =0x22222222
	ldr		r2, =0x33333333
	ldr		r3, =0x44444444
	svc		#0

	pop		{r0-r7, pc}

	.thumb_func
	.globl   Exception_test
Exception_test:
	push	{r0-r7, lr}					/* Save registers to stack , thumbe only support r0-r7 */
	add     r7, sp, #0					/* Save sp to r7 */

	bl		Privileged_test				/* Test privileged and svc */
	bl		Exception_stacking_test		/* Test stacking */

	mov		sp, r7						/* Restore sp */
	pop		{r0-r7, pc}					/* Restore registers */
