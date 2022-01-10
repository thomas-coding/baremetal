/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/*----------------------------------------------------------------------------
  Definitions
 *----------------------------------------------------------------------------*/
#define USR_MODE 0x10            // User mode
#define FIQ_MODE 0x11            // Fast Interrupt Request mode
#define IRQ_MODE 0x12            // Interrupt Request mode
#define SVC_MODE 0x13            // Supervisor mode
#define ABT_MODE 0x17            // Abort mode
#define UND_MODE 0x1B            // Undefined Instruction mode
#define SYS_MODE 0x1F            // System mode

Vectors:
	b	Reset_Handler
	b	.

	.globl   Reset_Handler
Reset_Handler:
	mov		r0, #1
	mov		r1, #2
	mov		r2, #3

	/* Set stack address, the end of secure sram */
	LDR		SP, =Image$$SVC_STACK$$ZI$$Limit

	bl		main
	b		.

