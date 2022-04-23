/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Embedded RAM Configuration, refer README.md memory map define */
__FLASH_BASE = 0x10200000;
__FLASH_SIZE = 0x200000;
__RAM_BASE = 0x20200000;
__RAM_SIZE = 0x200000;

__STACK_SIZE = 0x00010000;

MEMORY
{
	FLASH (rx) : ORIGIN = __FLASH_BASE, LENGTH = __FLASH_SIZE
	RAM (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

ENTRY(Reset_Handler)

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
	} > RAM AT > FLASH

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
