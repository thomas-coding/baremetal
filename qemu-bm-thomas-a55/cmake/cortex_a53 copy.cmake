# Name of the target
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-a53)
set(MCPU_FLAGS "-march=armv8.2-a")
set(VFP_FLAGS "")
set(SPEC_FLAGS "--specs=nosys.specs")

include(${CMAKE_CURRENT_LIST_DIR}/aarch64-none-elf.cmake)