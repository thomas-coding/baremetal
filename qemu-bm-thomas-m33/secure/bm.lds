/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Embedded RAM Configuration, refer README.md memory map define */
__FLASH_BASE = 0x10000000;
__FLASH_SIZE = 0x200000;
__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x200000;


__NSC_BASE = 0x10100000;
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

	.nsc (__NSC_BASE): ALIGN (32)
	{
		. = ALIGN(32);
		*(.nsc*)
		. = ALIGN(32);
	} > FLASH

	.stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE) :
	{
		. = . + __STACK_SIZE;
		__StackTop = .;
    } > RAM

}
