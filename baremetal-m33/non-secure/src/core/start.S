/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__Vectors:
	.long    __StackTop                         /*     Top of Stack */
	.long    Reset_Handler                      /*     Reset Handler */
	.long    NMI_Handler                        /* -14 NMI Handler */
	.long    HardFault_Handler                  /* -13 Hard Fault Handler */
	.long    MemManage_Handler                  /* -12 MPU Fault Handler */
	.long    BusFault_Handler                   /* -11 Bus Fault Handler */
	.long    UsageFault_Handler                 /* -10 Usage Fault Handler */
	.long    0                                  /*     Reserved */
	.long    0                                  /*     Reserved */
	.long    0                                  /*     Reserved */
	.long    0                                  /*     Reserved */
	.long    SVC_Handler                        /*  -5 SVC Handler */
	.long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
	.long    0                                  /*     Reserved */
	.long    PendSV_Handler                     /*  -2 PendSV Handler */
	.long    SysTick_Handler                    /*  -1 SysTick Handler */

	.space   (214 * 4)                          /* Interrupts 10 .. 224 are left out */

	.thumb_func
	.globl   Reset_Handler
Reset_Handler:
	mov		r0, #0
	mov		r1, #1
	mov		r2, #2
	mov		r3, #3
	mov		r4, #4
	mov		r5, #5
	mov		r6, #6
	mov		r7, #7
#	bl		Assemble_learn
	mov		r7, #6
#	bl		Exception_test
	bl		main
	mov		r3, #4
	b		.
	mov		r2, #4


Default_Handler:
                b        .

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

