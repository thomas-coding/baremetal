1、编译运行
==========================================

| Makefile等在M3实验中已详细说明，这里不再赘述。
| 这小节代码完整实现请查看：https://github.com/thomas-coding/baremetal

1.1 代码
-------------------------------------------

先用一行汇编，看下arm系列的编译，elf情况

.. code-block:: asm

	Vectors:
		b	Reset_Handler
		b	.

		.globl   Reset_Handler
	Reset_Handler:
		mov		r0, #1
		mov		r1, #2
		mov		r2, #3
		b		.



::

	MEMORY
	{
		FLASH (rwx) : ORIGIN = 0, LENGTH = 0x08000000
	}

	ENTRY(Reset_Handler)

	SECTIONS
	{
		.text :
		{
			*(.text*)
		} > FLASH
	}

链接脚本，从0地址开始放，只有代码段

.. note::
 makefile链接flag修改为-nostdlib -mcpu=cortex-a15


1.2 qemu命令行
-------------------------------------------

.. code-block:: sh

	qemu_option+=" -machine virt,secure=on -cpu cortex-a15"
	qemu_option+=" -bios ${shell_folder}/output/target.bin"
	qemu_option+=" -nographic"

1.3 运行结果
-------------------------------------------

::

	=> 0x0 <Vectors>:       b       0x8 <Reset_Handler>
	(gdb) si
	0x00000008 in Reset_Handler ()
	1: x/i $pc
	=> 0x8 <Reset_Handler>: mov     r0, #1
	(gdb) si
	0x0000000c in Reset_Handler ()
	1: x/i $pc
	=> 0xc <Reset_Handler+4>:       mov     r1, #2
	(gdb) info reg r0
	r0             0x1                 1

.. note::
 开头pc在 0x0 地址，然后跳转到0x8 的 Reset_Handler ，给 r0 赋值为1，执行完看赋值成功了。最后会进入循环。

1.4 Memory layout
-------------------------------------------

.. code-block:: c

	static const MemMapEntry base_memmap[] = {
		/* Space up to 0x8000000 is reserved for a boot ROM */
		[VIRT_FLASH] =              {          0, 0x08000000 },
		[VIRT_CPUPERIPHS] =         { 0x08000000, 0x00020000 },
		/* GIC distributor and CPU interfaces sit inside the CPU peripheral space */
		[VIRT_GIC_DIST] =           { 0x08000000, 0x00010000 },
		[VIRT_GIC_CPU] =            { 0x08010000, 0x00010000 },
		[VIRT_GIC_V2M] =            { 0x08020000, 0x00001000 },
		[VIRT_GIC_HYP] =            { 0x08030000, 0x00010000 },
		[VIRT_GIC_VCPU] =           { 0x08040000, 0x00010000 },
		/* The space in between here is reserved for GICv3 CPU/vCPU/HYP */
		[VIRT_GIC_ITS] =            { 0x08080000, 0x00020000 },
		/* This redistributor space allows up to 2*64kB*123 CPUs */
		[VIRT_GIC_REDIST] =         { 0x080A0000, 0x00F60000 },
		[VIRT_UART] =               { 0x09000000, 0x00001000 },
		[VIRT_RTC] =                { 0x09010000, 0x00001000 },
		[VIRT_FW_CFG] =             { 0x09020000, 0x00000018 },
		[VIRT_GPIO] =               { 0x09030000, 0x00001000 },
		[VIRT_SECURE_UART] =        { 0x09040000, 0x00001000 },
		[VIRT_SMMU] =               { 0x09050000, 0x00020000 },
		[VIRT_PCDIMM_ACPI] =        { 0x09070000, MEMORY_HOTPLUG_IO_LEN },
		[VIRT_ACPI_GED] =           { 0x09080000, ACPI_GED_EVT_SEL_LEN },
		[VIRT_NVDIMM_ACPI] =        { 0x09090000, NVDIMM_ACPI_IO_LEN},
		[VIRT_PVTIME] =             { 0x090a0000, 0x00010000 },
		[VIRT_SECURE_GPIO] =        { 0x090b0000, 0x00001000 },
		[VIRT_MMIO] =               { 0x0a000000, 0x00000200 },
		/* ...repeating for a total of NUM_VIRTIO_TRANSPORTS, each of that size */
		[VIRT_PLATFORM_BUS] =       { 0x0c000000, 0x02000000 },
		[VIRT_SECURE_MEM] =         { 0x0e000000, 0x01000000 },
		[VIRT_PCIE_MMIO] =          { 0x10000000, 0x2eff0000 },
		[VIRT_PCIE_PIO] =           { 0x3eff0000, 0x00010000 },
		[VIRT_PCIE_ECAM] =          { 0x3f000000, 0x01000000 },
		/* Actual RAM size depends on initial RAM and device memory settings */
		[VIRT_MEM] =                { GiB, LEGACY_RAMLIMIT_BYTES },
	};

qemu 代码hw/arm/virt.c，看memory map


