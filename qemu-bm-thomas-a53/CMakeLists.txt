cmake_minimum_required(VERSION 3.12.0)

# Set up the project
project(thomas-a53
    LANGUAGES C ASM
)

# --------------------------------- Secure target ----------------------------------
set(TARGET "thomas-a53")
enable_language( C ASM )

include(config.cmake)

# Source
aux_source_directory(. SRC_LIST)
set(SRC_LIST
    ${SRC_LIST}
    ${CMAKE_HOME_DIRECTORY}/src/core/startup.S
    ${CMAKE_HOME_DIRECTORY}/src/core/v8_aarch64.S
    ${CMAKE_HOME_DIRECTORY}/src/main.c
    ${CMAKE_HOME_DIRECTORY}/src/common/common.c
    ${CMAKE_HOME_DIRECTORY}/src/common/console.c
    ${CMAKE_HOME_DIRECTORY}/src/common/kermit.c
    ${CMAKE_HOME_DIRECTORY}/src/common/tiny_command.c
    ${CMAKE_HOME_DIRECTORY}/src/common/tiny_console.c
    ${CMAKE_HOME_DIRECTORY}/src/common/devices.c
    ${CMAKE_HOME_DIRECTORY}/src/drivers/ns16550/ns16550.c
    ${CMAKE_HOME_DIRECTORY}/src/board/ns16550/board-ns16550.c
    )

# Target
add_executable(${TARGET}.elf "")

target_link_options(${TARGET}.elf PRIVATE -T ${CMAKE_HOME_DIRECTORY}/bm.lds
    -Wl,-Map=linkmap.txt,--build-id=none  -Wl,--print-memory-usage -nostartfiles)

target_include_directories(${TARGET}.elf PUBLIC
    .
    ./src/core
    ./src/common
    ./src/drivers/ns16550
    ./src/board
    ./src/board/ns16550
    )

target_sources(${TARGET}.elf
    PRIVATE
    ${SRC_LIST}
)

add_custom_target(${TARGET}.bin ALL
    COMMAND ${OBJCOPY} -O binary ${TARGET}.elf ${TARGET}.bin
    COMMAND ${OBJDUMP} -xd ${TARGET}.elf > ${TARGET}.asm
    DEPENDS ${TARGET}.elf
)

