#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)


export PATH="/root/workspace/.toolchains/gcc-arm-none-eabi-10.3-2021.10/bin/:$PATH"

# gdb
arm-none-eabi-gdb \
-ex 'target remote localhost:1234' \
-ex "add-symbol-file ${shell_folder}/secure/output/target_s.elf" \
-ex "add-symbol-file ${shell_folder}/non-secure/output/target_ns.elf" \
-q
 