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

qemu_option+=" -machine thomas-m3 -monitor null -semihosting"
qemu_option+=" --semihosting-config enable=on,target=native"
qemu_option+=" -kernel ${shell_folder}/output/target.elf"
qemu_option+=" -serial stdio -nographic"
qemu_option+=" -d guest_errors"

# Run qemu
#qemu-system-arm ${qemu_option}

# Change to develop qemu
#gdb --args ../../qemu/build/arm-softmmu/qemu-system-arm ${qemu_option}
#gdb --args ../../qemu/build/arm-softmmu/qemu-system-arm -d in_asm,out_asm,cpu ${qemu_option}
../../qemu/build/arm-softmmu/qemu-system-arm ${qemu_option}
