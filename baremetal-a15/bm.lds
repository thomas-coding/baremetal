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
	} > FLASH

	.stack (NOLOAD):
	{
		. = ORIGIN(RAM) + LENGTH(RAM) -  0x00001000;
		. = ALIGN(8);

		Image$$SVC_STACK$$ZI$$Base = .;
		. += 0x00001000;
		Image$$SVC_STACK$$ZI$$Limit = .;

	} > RAM
}
