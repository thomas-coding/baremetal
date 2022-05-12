This file will introduce how to build a new baremetal project which include
Cortex-M3 core, nvic and systick. if there are some uncertain description, Please let me known by email.

Author: Jinping Wu <wunekky@gmail.com>

The baremetal project build steps in Linux environment:

1. Install ARM cross compiler, then update $PATH in "build.sh":

        $ export PATH=[your_arm_toolchain_path]:$PATH

2. Build Baremetal
    We have one parameters to build the bare-metal.

        TARGET: which test case to build
            options:
                a                        - all modules
                c                        - clean

        e.g.
            ./build.sh a

        You can find target.elf and target.bin in the output directories.
        alius-bm-m0p.elf can be used on QEMU or DS5.
        alius-bm-m0p.bin can be used on FPGA.

3. Edit "runqemu.sh" and "rungdb.sh", update $PATH with QEMU path and toolchain path
		export PATH="your_qemu_path:$PATH"

4. Run qemu and gdb(create two new termial)
	./runqemu.sh  or ./runqemu.sh --gdb
	./rungdb.sh

5. Memory map (qemu/hw/arm/thomas_a15.c)
	/* Thomas-a15 memory map
	*
	*  0x00000000 .. 0x01ffffff : Flash(32M)
	*  0x10000000 .. 0x11ffffff : SRAM(32M)
	*  0x20000000 .. 0x27ffffff : DDR(128M)
	*  0x40000000 .. 0x40000fff : UART(4K)
	*  0x50000000 .. 0x50000fff : Thomas Test Device(4K)
	*  0x60000000 .. 0x6000ffff : GIC Distributor(64K)
	*  0x61000000 .. 0x6001ffff : GIC Redistributor(128K)
	*/
