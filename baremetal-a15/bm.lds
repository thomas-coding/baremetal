/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */


MEMORY
{
	FLASH (rwx) : ORIGIN = 0, LENGTH = 0x08000000
}

ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		*(.text*)
	} > FLASH
}
