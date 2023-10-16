/* Copyright (c) 2020 SiFive Inc. */
/* SPDX-License-Identifier: Apache-2.0 */
/* freedom-e-sdk/bsp/qemu-sifive-e31/metal.default.lds */
/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */
OUTPUT_ARCH("riscv")

__STACK_SIZE = 0x00010000;
__HEAP_SIZE = 0x00010000;

MEMORY
{
	rom (rx) : ORIGIN = 0x20000000, LENGTH = 32M
	ram (rwx) : ORIGIN = 0x40000000, LENGTH = 32M
}

ENTRY(_enter)

SECTIONS
{
    /* Each hart is allocated its own stack of size __stack_size. This value
     * can be overriden at build-time by adding the following to CFLAGS:
     *
     *     -Xlinker --defsym=__stack_size=0xf00
     *
     * where 0xf00 can be replaced with a multiple of 16 of your choice.
     *
     * __stack_size is PROVIDE-ed as a symbol so that initialization code
     * initializes the stack pointers for each hart at the right offset from
     * the _sp symbol.
     */
    __stack_size = DEFINED(__stack_size) ? __stack_size : __STACK_SIZE;
    PROVIDE(__stack_size = __stack_size);

    /* The size of the heap can be overriden at build-time by adding the
     * following to CFLAGS:
     *
     *     -Xlinker --defsym=__heap_size=0xf00
     *
     * where 0xf00 can be replaced with the value of your choice.
     *
     * Altertatively, the heap can be grown to fill the entire remaining region
     * of RAM by adding the following to CFLAGS:
     *
     *     -Xlinker --defsym=__heap_max=1
     *
     * Note that depending on the memory layout, the bitness (32/64bit) of the
     * target, and the code model in use, this might cause a relocation error.
     */
    __heap_size = DEFINED(__heap_size) ? __heap_size : __HEAP_SIZE;

    /* The boot hart sets which hart runs the pre-main initialization routines,
     * including copying .data into RAM, zeroing the BSS region, running
     * constructors, etc. After initialization, the boot hart is also the only
     * hart which runs application code unless the application overrides the
     * secondary_main() function to start execution on secondary harts.
     */
    PROVIDE(__metal_boot_hart = 0);

    /* ROM SECTION
     *
     * The following sections contain data which lives in read-only memory, if
     * such memory is present in the design, for the entire duration of program
     * execution.
     */
    .init : {
        /* The _enter symbol is placed in the .text.metal.init.enter section
         * and must be placed at the beginning of the program */
        KEEP (*(.text.metal.init.enter))
        KEEP (*(.text.metal.init.*))
        KEEP (*(SORT_NONE(.init)))
        KEEP (*(.text.libgloss.start))
    } >rom

    .fini : {
        KEEP (*(SORT_NONE(.fini)))
    } >rom

    .preinit_array : ALIGN(8) {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >rom

    .init_array : ALIGN(8) {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >rom

    .fini_array : ALIGN(8) {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
        KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >rom

    .rodata : {
        *(.rdata)
        *(.rodata .rodata.*)
        *(.gnu.linkonce.r.*)
        . = ALIGN(8);
        *(.srodata.cst16)
        *(.srodata.cst8)
        *(.srodata.cst4)
        *(.srodata.cst2)
        *(.srodata .srodata.*)
    } >rom

	/* ROM SECTION
     *
     * XIP flash, text also located in ROM
     */
    .text : {
        *(.text.unlikely .text.unlikely.*)
        *(.text.startup .text.startup.*)
        *(.text .text.*)
        *(.gnu.linkonce.t.*)
    } >rom

    /* RAM SECTION
     *
     * The following sections contain data which is copied from read-only
     * memory into an instruction tightly-integrated memory (ITIM), if one
     * is present in the design, during pre-main program initialization.
     *
     * Generally, the data copied into the ITIM should be performance-critical
     * functions which benefit from low instruction-fetch latency.
     */
    .data : ALIGN(8) {
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        . = ALIGN(8);
        PROVIDE( __global_pointer$ = . + 0x800 );
        *(.sdata .sdata.* .sdata2.*)
        *(.gnu.linkonce.s.*)
    } >ram AT>rom
    PROVIDE( metal_segment_data_source_start = LOADADDR(.data) );
    PROVIDE( metal_segment_data_target_start = ADDR(.data) );
    PROVIDE( metal_segment_data_target_end = ADDR(.data) + SIZEOF(.data) );

    .bss (NOLOAD): ALIGN(8) {
        *(.sbss*)
        *(.gnu.linkonce.sb.*)
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
    } >ram
    PROVIDE( metal_segment_bss_source_start = LOADADDR(.bss) );
    PROVIDE( metal_segment_bss_target_start = ADDR(.bss) );
    PROVIDE( metal_segment_bss_target_end = ADDR(.bss) + SIZEOF(.bss) );

    .stack (NOLOAD) : ALIGN(16) {
        PROVIDE(metal_segment_stack_begin = .);
        . += __stack_size; /* Hart 0 */
        PROVIDE( _sp = . );
        PROVIDE(metal_segment_stack_end = .);
    } >ram

    .heap (NOLOAD) : ALIGN(8) {
        PROVIDE( __end = . );
        PROVIDE( __heap_start = . );
        PROVIDE( metal_segment_heap_target_start = . );
        . = __heap_size;
        PROVIDE( metal_segment_heap_target_end = . );
        PROVIDE( _heap_end = . );
        PROVIDE( __heap_end = . );
    } >ram

    /* C++ exception handling information is
     * not useful with our current runtime environment,
     * and it consumes flash space. Discard it until
     * we have something that can use it
     */
    /DISCARD/ : {
	*(.eh_frame .eh_frame.*)
    }
}
