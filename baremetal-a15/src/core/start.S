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
	ldr		SP, =Image$$SVC_STACK$$ZI$$Limit

	/* Copy .data from flash to sram */
	/* Read copy table, copy form r1 to r2, length is r3 */
	ldr		r0, = __copy_table_start__
	ldr		r1, [r0]
	ldr		r2, [r0, #4]
	ldr		r3, [r0, #8]

	/* r3-4, if result < 0, branch to done */
.L_loop0_0:
	subs	r3, #4
	blt		.L_loop0_0_done
	ldr		r0, [r1, r3]
	str		r0, [r2, r3]
	b		.L_loop0_0
.L_loop0_0_done:

	bl		main
	b		.

