/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */


MEMORY
{
	FLASH (rx) : ORIGIN = 0, LENGTH = 0x08000000
	TTB (rw) : ORIGIN = 0x0e000000, LENGTH = 0x00040000
	RAM (rwx)  : ORIGIN = 0x0e100000, LENGTH = 0x00f00000
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

	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
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
		. = ORIGIN(RAM) + LENGTH(RAM) -  0x00001000;
		. = ALIGN(8);
		Image$$SVC_STACK$$ZI$$Base = .;
		. += 0x00001000;
		Image$$SVC_STACK$$ZI$$Limit = .;
	} > RAM
}
