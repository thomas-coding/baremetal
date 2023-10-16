/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Core-Local Interruptor (CLINT) driver
 *
 */

#include "common.h"
#include "m_trap.h"
#include "interrupt.h"

void __attribute__((weak)) timer_interrupt_handler(void)
{
    csr_clear(CSR_MIE, MIP_MTIP);
}

struct trap_regs *trap_handler(struct trap_regs *regs)
{
    uint32_t mcause = csr_read(CSR_MCAUSE);

    vs_printf("mcause:0x%08x\n", mcause);

    mcause &= ~(1UL << (__riscv_xlen - 1));
    switch (mcause) {
    case IRQ_M_TIMER:
        timer_interrupt_handler();
        break;
    case IRQ_M_EXT:
        external_interrupt_handler();
        break;
    default:
        break;
    };

    return regs;
}
