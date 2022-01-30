/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

MEMORY
{
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

ENTRY(_start)

SECTIONS
{
	.text :
	{
		*(.text*)
		*(.rodata*)
	} > RAM

}
