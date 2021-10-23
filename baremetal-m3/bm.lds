/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Embedded RAM Configuration */
__RAM_BASE = 0x0;
__RAM_SIZE = 0x10000;


MEMORY
{
	RAM (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		*(.text*)
	} > RAM
}
