#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)

#export PATH="/opt/riscv/bin:$PATH"
export PATH="/opt/riscv32/bin:$PATH"
export PATH="/home/cn1396/.toolchain/riscv/riscv32-elf-ubuntu-20.04-nightly-2022.08.26-nightly/bin:$PATH"

cmd_help() {
	echo "Basic mode:"
	echo "$0 h			---> command help"
	echo "$0 a			---> make"
	echo "$0 c			---> make clean"
}

if [[ $1  = "h" ]]; then
	cmd_help
elif [[ $1  = "a" ]]; then
	make
elif [[ $1  = "c" ]]; then
	make clean
else
	echo "wrong args."
	cmd_help
fi
