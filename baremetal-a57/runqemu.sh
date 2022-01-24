#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)

export PATH="/root/workspace/software/qemu/qemu-6.0.0/build/:$PATH"
export PATH="/home/cn1396/workspace/software/qemu/qemu-6.0.0/build/:$PATH"

qemu_option=
if [[ $1  = "--gdb" ]]; then
    qemu_option+=" -s -S"
    echo "enable gdb, please run script './rungdb', and enter c "
else
    echo "not use gdb, just run"
fi

qemu_option+=" -machine virt,secure=on -cpu cortex-a57"
qemu_option+=" -bios ${shell_folder}/output/target.bin"
qemu_option+=" -nographic -m 128 "
#qemu_option+="  -smp 2"

# run qemu
qemu-system-aarch64 ${qemu_option}