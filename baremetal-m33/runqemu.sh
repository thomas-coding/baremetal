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

qemu_option+=" -machine mps2-an521 -monitor null -semihosting"
qemu_option+=" --semihosting-config enable=on,target=native"
qemu_option+=" -device loader,file=non-secure/output/target_ns.bin,addr=0x100000"
qemu_option+=" -kernel ${shell_folder}/secure/output/target_s.elf"
qemu_option+=" -serial stdio -nographic"

# Run qemu
#qemu-system-arm ${qemu_option}

# Change to develop qemu
../../qemu/build/arm-softmmu/qemu-system-arm ${qemu_option}
