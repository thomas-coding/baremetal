#!/bin/bash

# Shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)

export PATH="/root/workspace/software/qemu/qemu-6.0.0/build/:$PATH"

qemu_option=
if [[ $1  = "--gdb" ]]; then
    qemu_option+=" -s -S"
    echo "enable gdb, please run script './rungdb', and enter c "
else
    echo "not use gdb, just run"
fi

qemu_option+=" -machine virt -bios none -monitor null -semihosting"
qemu_option+=" --semihosting-config enable=on,target=native"
qemu_option+=" -kernel ${shell_folder}/output/target.elf"
qemu_option+=" -serial stdio -nographic"

# Run qemu
#qemu-system-riscv64 ${qemu_option}
qemu-system-riscv32 ${qemu_option}

