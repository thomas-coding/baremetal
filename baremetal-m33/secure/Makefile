# ------------------------
# Generic Makefile
# ------------------------

# Project name
Target = target
ELF = ${Target}.elf

CPU = cortex-m33
TARGET_ARCH	= -mcpu=$(CPU)

# Compile command and flag
CC = arm-none-eabi-gcc
CFLAG = -Wall -mthumb -g
ASFLAGS = -g

# Linker command and flag
LINKER = arm-none-eabi-gcc
#LDFLAGS	= -nostdlib -e 0x0 -Ttext=0x0 -mcpu=cortex-m3
#LDFLAGS	= -nostdlib -mcpu=cortex-m3 -T bm.lds
LDFLAGS	= -nostdlib -mcpu=cortex-m33  -T bm.lds

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
	@echo ""
	$(LINKER)  $(LDFLAGS) -o $@ $(OBJ_FILES)
	@$(DUMP) -xD $@ > $(BIN_DIR)/$(Target).asm
	@$(OBJCOPY) -O binary  $@  $(BIN_DIR)/$(Target).bin
	@xxd $(BIN_DIR)/$(Target).bin > $(BIN_DIR)/$(Target).hex
#	@echo "Linking complete!"

# Compile .c to .o
obj/%.o : src/%.c
#	@echo Compiling $< to $@
	$(CC) $(CFLAG) $(INCLUDES) $(TARGET_ARCH) -c $< -o $@

# Compile .S to .o
obj/%.o : src/%.S
#	@echo Compiling $< to $@
	$(CC) $(ASFLAGS) -c $(TARGET_ARCH) $< -o $@


PHONY: clean 
clean :
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Cleanup complete!"

$(OBJ_DIRS):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@
