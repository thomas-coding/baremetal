/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

	.section startup, "ax"
	.balign 0x20


	.globl   start
start:
	mov		x0, #1
	mov		x1, #2
	mov		x2, #3
	mov		x3, #4
	mov		x4, #5
	mov		x5, #6
	mov		x6, #7
	mov		x7, #8

