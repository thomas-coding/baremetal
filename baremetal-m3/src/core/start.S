/*
 * Copyright (c) 2021-2008, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__Vectors:
	.long		0x12345678			/*     Top of Stack */
	.long		Reset_Handler		/*     Reset Handler */
	.long		0x11111111		
	.long		0x22222222		

	.thumb_func
Reset_Handler:
	mov		r0, #1
	mov		r1, #2
	mov		r2, #3
	b		.
	mov		r2, #4
