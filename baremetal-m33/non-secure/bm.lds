/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Embedded RAM Configuration */
__RAM_BASE = 0x100000;
__RAM_SIZE = 0x400000; /*4M*/

__STACK_SIZE = 0x00010000;

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
