/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */


MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x08000000
	TTB (rw) : ORIGIN = 0x0e000000, LENGTH = 0x00040000
	RAM (rwx)  : ORIGIN = 0x40000000, LENGTH = 0x00f00000
	/* RAM (rwx)  : ORIGIN = 0x0e100000, LENGTH = 0x00f00000 */
}

ENTRY(start)

SECTIONS
{
	.vectors :
	{
		KEEP(*(startup))
	} > FLASH

	.text :
	{
		*(.text*)
		*(.rodata*)
	} > FLASH

	.stack (NOLOAD):
	{
		. = ALIGN(64);
		. = . + 8 * 0x1000;
		__stack = .;
	} > RAM
}
