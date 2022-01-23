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


	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		QUAD (__etext)
		QUAD (__data_start__)
		QUAD (__data_end__ - __data_start__)
		__copy_table_end__ = .;
	} > FLASH

	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		QUAD (__bss_start__)
		QUAD (__bss_end__ - __bss_start__)
		__zero_table_end__ = .;
	} > FLASH

	__etext = .;

	.ARM_TLB (NOLOAD):
	{
		/* 4K * 4 TTB */
		. = ALIGN(0x4000);
	} > TTB

	.data : AT(__etext)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(.data*)
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	.bss ALIGN(16):
	{
		__bss_start__ = .;
		*(.bss*)
		__bss_end__ = .;
	} > RAM

	.stack (NOLOAD):
	{
		. = ALIGN(64);
		. = . + 8 * 0x1000;
		__stack = .;
	} > RAM
}
