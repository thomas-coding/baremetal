/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Embedded RAM Configuration */
__RAM_BASE = 0x10000000;
__RAM_SIZE = 0x200000; /*2M*/

__STACK_SIZE = 0x00080000;

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

	.nsc (0x10100000): ALIGN (32)
	{
		. = ALIGN(32);
		*(.nsc*)
		. = ALIGN(32);
	} > RAM

	.stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE) :
	{
		. = . + __STACK_SIZE;
		__StackTop = .;
    } > RAM

}
