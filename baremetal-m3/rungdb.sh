#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)


export PATH="/root/workspace/.toolchains/gcc-arm-none-eabi-10-2020-q4-major/bin/:$PATH"

# gdb
arm-none-eabi-gdb \
-ex 'target remote localhost:1234' \
-ex "add-symbol-file ${shell_folder}/output/target.elf" \
-q
 