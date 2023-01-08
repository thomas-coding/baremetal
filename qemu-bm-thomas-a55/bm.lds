/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

/* Thomas-a55 memory map
 *
 *  0x10000000 .. 0x11ffffff : Flash(32M)
 *  0x20000000 .. 0x21ffffff : SRAM(32M)
 *  0x30000000 .. 0x3fffffff : DDR(256M)
 *  0x40000000 .. 0x40000fff : UART(4K)
 *  0x60000000 .. 0x6000ffff : GIC Distributor(64K)
 *  0x61000000 .. 0x6001ffff : GIC Redistributor(128K)
 */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 0x02000000
	RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 0x02000000
	DDR (rwx)  : ORIGIN = 0x30000000, LENGTH = 0x08000000
}

ENTRY(start64)

SECTIONS
{
	.vectors :
	{
		__code_start = .;
		KEEP(*(StartUp))
	} > RAM

	.text :
	{
		*(.text*)
	} > RAM

	.rodata :
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	} > RAM

	.data :
	{
		__data_start = . ;
		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
	} > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	.heap (NOLOAD):
	{
		. = ALIGN(64);
		__end__ = .;
		PROVIDE(end = .);
		. = . + 0x1000;
	} > RAM

	.stack (NOLOAD):
	{
		. = ALIGN(64);
		. = . + 8 * 0x1000;
		__stack = .;
	} > RAM

    .el3_stack (NOLOAD):
    {
        . = ALIGN(64);
        . = . + 8 * 0x1000;
        __el3_stack = .;
    }

	.irq_stacks (NOLOAD):
	{
		. = ALIGN(64);
		. = . + 4 * 256;
		__irq_stack = .;
	} > RAM

	.fiq_stacks (NOLOAD):
	{
		. = ALIGN(64);
		. = . + 4 * 256;
		__fiq_stack = .;
	} > RAM

	.ARM_TLB :
	{
		. = ALIGN(0x4000);
	} > RAM
}

