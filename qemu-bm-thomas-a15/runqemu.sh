#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)

export PATH="/root/workspace/software/qemu/qemu-6.0.0/build/:$PATH"

qemu_option=
if [[ $1  = "--gdb" ]]; then
    qemu_option+=" -s -S"
    echo "enable gdb, please run script './rungdb', and enter c "
else
    echo "not use gdb, just run"
fi

qemu_option+=" -machine thomas-a15"
#qemu_option+=" -bios ${shell_folder}/output/target.bin"
qemu_option+=" -kernel ${shell_folder}/output/target.elf"
qemu_option+=" -nographic -m 256 "
#qemu_option+="  -smp 2"
qemu_option+=" -d guest_errors"

# run qemu
../../qemu/build/arm-softmmu/qemu-system-arm ${qemu_option}