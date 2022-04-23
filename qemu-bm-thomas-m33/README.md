This file will introduce how to build a new baremetal project which include
Cortex-M3 core, nvic and systick. if there are some uncertain description, Please let me known by email.

Author: Jinping Wu <wunekky@gmail.com>

The baremetal project build steps in Linux environment:

1. Install ARM cross compiler, then update $PATH in "build.sh":

        $ export PATH=[your_arm_toolchain_path]:$PATH

2. Build Baremetal
   	2.1 Build Secure image
	cd secure
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

5. Thomas-m33 memory map
	5.1 QEMU hardware define:
	/*
	*  0x00000000 .. 0x0fffffff : Reserved
	*  0x10000000 .. 0x103fffff : Flash(4M)
	*  0x20000000 .. 0x203fffff : SRAM(4M)
	*  0x40000000 .. 0x40000fff : APB UART(4K)
	*  0x50000000 .. 0x50000fff : Thomas Test Device(4K)
	*/

	5.2 Software define:
	/*
	*  0x00000000 .. 0x0fffffff : Reserved
	*  0x10000000 .. 0x101fffff : Secure Flash(2M)
	  *  0x10000000 .. 0x100fffff : Secure code(1M)
	  *  0x10100000 .. 0x101fffff : Non-Secure-callable code(1M)
	*  0x10200000 .. 0x103fffff : Non-Secure Flash(2M)
	*  0x20000000 .. 0x201fffff : Secure SRAM(2M)
	*  0x20200000 .. 0x203fffff : Non-Secure SRAM(2M)
	*  0x40000000 .. 0x40000fff : APB UART(4K)
	*  0x50000000 .. 0x50000fff : Thomas Test Device(4K)
	*/