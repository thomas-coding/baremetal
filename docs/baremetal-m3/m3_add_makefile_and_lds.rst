3、Makefile 和 链接脚本
==========================================

当前需要修改代码目录如下，通过makefile来编译，build.sh中指定toolchain，调用make，runqemu.sh 和 rungdb.sh 用于运行 elf 和调试。

::

	root@iZj6ccyu2ndokc2ujnox0tZ:~/workspace/code/baremetal/baremetal-m3# tree
	.
	├── bm.lds
	├── build.sh
	├── Makefile
	├── README.md
	├── rungdb.sh
	├── runqemu.sh
	└── src
		├── board
		├── core
		│   └── start.S
		└── test    


3.1 Makefile
-------------------------------------------

参考：
https://makefile-study.readthedocs.io/zh_CN/latest/

.. code-block:: Makefile

	# ------------------------
	# Generic Makefile
	# ------------------------

	# Project name
	Target = target
	ELF = ${Target}.elf

	CPU = cortex-m3
	TARGET_ARCH	= -mcpu=$(CPU)

	# Compile command and flag
	CC = arm-none-eabi-gcc
	CFLAG = -Wall -mthumb
	ASFLAGS =

	# Linker command and flag
	LINKER = arm-none-eabi-gcc
	LDFLAGS	= -nostdlib -e 0x0 -Ttext=0x0 -mcpu=cortex-m3

	DUMP = arm-none-eabi-objdump
	OBJCOPY = arm-none-eabi-objcopy

	# Dir
	SRC_DIR = src
	OBJ_DIR = obj
	BIN_DIR = output

	# Source directorys, find all source directory ,like src/board src/common
	SRC_DIRS	= $(shell find src -maxdepth 3 -type d)

	# OBJ_DIRS, change src to obj, match the source directorys, like obj/board obj/common
	OBJ_DIRS	:= $(foreach dir,$(SRC_DIRS),$(subst src,obj,$(dir)))

	# INCLUDES, add source directorys to include, like -Isrc/board -Isrc/common
	INCLUDES	= $(foreach dir, $(SRC_DIRS),-I$(dir))

	# Source files, c srouce files and asmeble source files. like src/board/test.c src/board/test.S
	C_SRC	+= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
	S_SRC	:= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.S))

	# OBJ files, object files. like obj/board/test.o obj/board/test.o
	OBJ_S_FILES	:= $(foreach file,$(S_SRC),$(patsubst %.S,%.o,$(subst src,obj,$(file))))
	OBJ_C_FILES	:= $(foreach file,$(C_SRC),$(patsubst %.c,%.o,$(subst src,obj,$(file))))
	OBJ_FILES	:= $(OBJ_S_FILES) $(OBJ_C_FILES)

	# 1. Create obj directorys and bin directory
	# 2. Comple all OBJ_FILES, from .c .S to .o
	# 3. Link all .o to binary target
	$(BIN_DIR)/$(ELF) : $(OBJ_DIRS) $(BIN_DIR) $(OBJ_FILES)
		$(LINKER)  $(LDFLAGS) -o $@ $(OBJ_FILES)
		$(DUMP) -xD $@ > $(BIN_DIR)/$(Target).asm
		$(OBJCOPY) -O binary  $@  $(BIN_DIR)/$(Target).bin
		xxd $(BIN_DIR)/$(Target).bin > $(BIN_DIR)/$(Target).hex
		@echo "Linking complete!"

	# Compile .c to .o
	obj/%.o : src/%.c
		@echo Compiling $< to $@
		$(CC) $(CFLAG) $(INCLUDES) $(TARGET_ARCH) -c $< -o $@

	# Compile .S to .o
	obj/%.o : src/%.S
		@echo $@ Compiling $< to $@
		$(CC) $(ASFLAGS) -c $(TARGET_ARCH) $< -o $@


	PHONY: clean 
	clean :
		rm -rf $(BIN_DIR) $(OBJ_DIR)
		@echo "Cleanup complete!"

	$(OBJ_DIRS):
		mkdir -p $@

	$(BIN_DIR):
		mkdir -p $@


.. note::
 Makefile 基本思路是查找src目录下所有 .c .S 文件，先各自编译成 .o， 再链接成 elf。


3.2 链接脚本
-------------------------------------------

| 之前我们是在链接时，直接指定参数 -e 0x0 -Ttext=0x0 来告诉gcc 代码段和入口地址的。现在我们需要把这部分用链接脚本来实现。
| 新建bm.lsd文件。

::

	__RAM_BASE = 0x0;
	__RAM_SIZE = 0x10000;


	MEMORY
	{
		RAM (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
	}

	ENTRY(Reset_Handler)

	SECTIONS
	{
		.text :
		{
			*(.text*)
		} > RAM
	}


.. code-block:: Makefile

	#LDFLAGS	= -nostdlib -e 0x0 -Ttext=0x0 -mcpu=cortex-m3
	LDFLAGS	= -nostdlib -mcpu=cortex-m3 -T bm.lds


.. note::
 只有一个section，把代码段放入到ram中，注意这个entry定义了入口，Reset_Handler需要在start.S中定义为globl（	.globl   Reset_Handler）。

