
/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

	.thumb_func
	.section .nsc,"aw"
	.globl   nsc_call
nsc_call:
	sg
	mov	  r5, lr
	bl    nsc_call_function
	bxns  r5

