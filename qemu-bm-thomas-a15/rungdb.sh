#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)


export PATH="/root/workspace/.toolchains/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/:$PATH"
export PATH="/home/cn1396/.toolchain/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin/:$PATH"

# gdb
arm-none-eabi-gdb \
-ex 'target remote localhost:1234' \
-ex "add-symbol-file ${shell_folder}/output/target.elf" \
-q
 