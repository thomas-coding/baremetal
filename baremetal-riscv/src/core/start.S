/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

.section .text.start

.globl _start
_start:
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	jal		x1, assemble_study
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop
	addi	x0, x0, 0 //nop



