This file will introduce how to build a new baremetal project which include
riscv core. if there are some uncertain description, Please let me known by email.

Author: Jinping Wu <wunekky@gmail.com>

The baremetal project build steps in Linux environment:

1. Install riscv cross compiler, then update $PATH in "build.sh":

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