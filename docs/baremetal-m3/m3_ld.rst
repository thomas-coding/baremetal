6、完善链接脚本
==========================================

| 之前代码中链接脚本只有一个text段，但是gcc在编译的时候，实际上会把rodata、data、bss以此生成并放入elf中
| 之前stack用了一个固定值，但是实际上如果代码和数据多了，会有冲突
| 我们这里的目标是手动来指定这些段，并且配置好stack，使链接脚本看起来更合理些


6.1 链接脚本 
-------------------------------------------

:: 

	/* Embedded RAM Configuration */
	__RAM_BASE = 0x0;
	__RAM_SIZE = 0x400000;

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


.. note::
	SRAM为4M，text、data、bss以此放入开头位置，stack放到4M最末尾，定义大小为64K


6.2 更新向量表 
-------------------------------------------

.. code-block:: asm

	/*
	* Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
	*
	* SPDX-License-Identifier: MIT
	*/

	__Vectors:
		.long		__StackTop				/*     Top of Stack */
		.long		Reset_Handler		/*     Reset Handler */
		.long		0x11111111		
		.long		0x22222222		

		.thumb_func
		.globl   Reset_Handler
	Reset_Handler:
		mov		r0, #1
		mov		r1, #2
		mov		r2, #3
		mov		r7, #6
		bl		main
		mov		r3, #4
		b		.
		mov		r2, #4

.. note::
	__StackTop由链接脚本提供，栈顶，把它放入异常向量表的0x0位置，core起来后，会把它赋值给MSP


这样，我们的链接脚本看起来完善一些了，stack也比较合理了。

.. note::
	我们这里都是在SRAM中，没有flash，因此data段不用搬移，当前位置就可以读写。bin文件中包含了text、rodata、data段。




