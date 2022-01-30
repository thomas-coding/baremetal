#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)


#export PATH="/opt/riscv/bin:$PATH"
export PATH="/opt/riscv32/bin:$PATH"

# gdb
#riscv64-unknown-linux-gnu-gdb \
riscv32-unknown-elf-gdb \
-ex 'target remote localhost:1234' \
-ex "add-symbol-file ${shell_folder}/output/target.elf" \
-q
 