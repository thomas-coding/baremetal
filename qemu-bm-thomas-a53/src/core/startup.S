/*
 * Startup Code for Armv8-A MPCore
 *
 * Refer to Armv8.2-A SMP bare-metal(fireworks_Cortex-A55_Cortex-A76)
 *
 * Copyright (c) 2014-2019 Arm Limited (or its affiliates). All rights reserved.
 * Use, modification and redistribution of this file is subject to your
 * possession of a valid End User License Agreement for the Arm Product of
 * which these examples are part of and your compliance with all applicable
 * terms and conditions of such licence agreement.
 */

	.section StartUp, "ax"
	.balign 4

/* ------------------------------------------------------------ */

	.global start64
	.type start64, "function"
start64:

	nop
	nop
	ldr x0, =0x1122334455667788
	nop
	nop

    // extract the core number from MPIDR_EL1 and store it in
    // x19 (defined by the AAPCS as callee-saved), so we can re-use
    // the number later
    //
    bl GetCPUID
    mov x19, x0

    //
    // Setup some EL3 stack space, ready for calling some subroutines, below.
    //
    // Stack space allocation is CPU-specific, so use CPU
    // number already held in x19
    //
    // 2^12 bytes per CPU for the EL3 stacks
    //
    ldr x0, =__el3_stack
    sub x0, x0, x19, lsl #12
    mov sp, x0

	bl main

	b .
