/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */


MEMORY
{
	FLASH (rx) : ORIGIN = 0, LENGTH = 0x08000000
	RAM (rwx)  : ORIGIN = 0x0e000000, LENGTH = 0x01000000
}

ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		*(.text*)
		*(.rodata*)
	} > FLASH

	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		__copy_table_end__ = .;
	} > FLASH

	__etext = .;

	.data : AT(__etext)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(.data*)
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	.stack (NOLOAD):
	{
		. = ORIGIN(RAM) + LENGTH(RAM) -  0x00001000;
		. = ALIGN(8);

		Image$$SVC_STACK$$ZI$$Base = .;
		. += 0x00001000;
		Image$$SVC_STACK$$ZI$$Limit = .;

	} > RAM
}
