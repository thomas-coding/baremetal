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

qemu_option+=" -machine virt,secure=on -cpu cortex-a15"
qemu_option+=" -bios ${shell_folder}/output/target.bin"
qemu_option+=" -nographic"

# run qemu
qemu-system-arm ${qemu_option}