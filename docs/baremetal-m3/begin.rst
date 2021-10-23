1、基础知识
==========================================




1.1 一行汇编
-------------------------------------------

先用一行汇编，看下arm系列的编译，elf情况

.. code-block:: asm

   	mov		r0, #1

使用交叉编译工具，先导出：

::

	export PATH="/root/workspace/.toolchains/gcc-arm-none-eabi-10-2020-q4-major/bin/:$PATH"

::

	arm-none-eabi-gcc test.S -nostdlib -o test.elf

.. note::
 gcc编译默认会包含C库，我们不需要，所以加上 -nostdlib ，源文件是test.S ， 目标文件是生成 test.elf

::

 	arm-none-eabi-objdump -xD test.elf > test.asm

DUMP出 ELF 内容，可以看到(部分内容)：


.. code-block:: python

	test.elf:     file format elf32-littlearm
	test.elf
	architecture: armv4t, flags 0x00000112:
	EXEC_P, HAS_SYMS, D_PAGED
	start address 0x00008000

	Program Header:
		LOAD off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**16
			filesz 0x00008004 memsz 0x00008004 flags r-x

	Sections:
	Idx Name          Size      VMA       LMA       File off  Algn
	0 .text         00000004  00008000  00008000  00008000  2**2

	1 .ARM.attributes 0000001a  00000000  00000000  00008004  2**0

	2 .noinit       00000000  00018004  00018004  0000801e  2**0

	Disassembly of section .text:

	00008000 <__bss_end__-0x10004>:
		8000:	e3a00001 	mov	r0, #1

elf格式，小端，arch是armv4t（我们编译时没有指定cpu，default值），.text 段放在了 0x8000 位置，只有一行代码，机器码是 e3a00001


::

	arm-none-eabi-objcopy -O binary test.elf test.bin

从 ELF 中导出可执行 binary 文件。我们一般 QEMU 会使用 ELF文件（qemu会解析），而实际的板子会使用bin文件，比如把bin文件烧到flash

::

	xxd test.bin

:: 

	root@iZj6ccyu2ndokc2ujnox0tZ:~/workspace/code/test# xxd test.bin 
	00000000: 0100 a0e3                                ....

Bin 文件中就一条机器指令，也就是 “mov	r0, #1” 这条汇编语句，翻译从 arm core 可以执行的机器指令。

.. note::
 编译链接涉及的内容很庞大，不在我们讨论范围内，只做简单说明，满足我们使用即可。


