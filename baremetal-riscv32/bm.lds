/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__STACK_SIZE = 0x00010000;

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

	.data :
	{
		*(.data*)
	} > RAM

	.bss :
	{
		*(.bss*)
	} > RAM

	.stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE) :
	{
		. = . + __STACK_SIZE;
		__StackTop = .;
    } > RAM
}
