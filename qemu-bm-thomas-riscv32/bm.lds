/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

__STACK_SIZE = 0x00010000;

MEMORY
{
	FLASH (rwx) : ORIGIN = 0x20000000, LENGTH = 32M
	RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 32M
}

ENTRY(_start)

SECTIONS
{
	.text :
	{
		*(.text*)
		*(.rodata*)
	} > FLASH

	.data :
	{
		*(.data*)
	} > FLASH

	.bss :
	{
		*(.bss*)
	} > FLASH

	.stack (ORIGIN(FLASH) + LENGTH(FLASH) - __STACK_SIZE) :
	{
		. = . + __STACK_SIZE;
		__StackTop = .;
    } > FLASH
}
