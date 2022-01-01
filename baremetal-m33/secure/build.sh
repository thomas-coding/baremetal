#!/bin/bash

# shell folder
shell_folder=$(cd "$(dirname "$0")" || exit;pwd)

export PATH="/root/workspace/.toolchains/gcc-arm-none-eabi-10-2020-q4-major/bin/:$PATH"

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
