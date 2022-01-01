#!/bin/bash


cmd_help() {
	echo "Basic mode:"
	echo "$0 h			---> command help"
	echo "$0 a			---> make"
	echo "$0 c			---> make clean"
}

if [[ $1  = "h" ]]; then
	cmd_help
elif [[ $1  = "a" ]]; then
	cd secure
	./build.sh a
	cd ../non-secure
	./build.sh a
elif [[ $1  = "c" ]]; then
	cd secure
	./build.sh c
	cd ../non-secure
	./build.sh c
else
	echo "wrong args."
	cmd_help
fi
