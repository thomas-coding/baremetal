/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __M_TRAP_H__
#define __M_TRAP_H__
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/** Representation of register state at time of trap/interrupt */
struct trap_regs {
    /** zero register state */
    unsigned long zero;
    /** ra register state */
    unsigned long ra;
    /** sp register state */
    unsigned long sp;
    /** gp register state */
    unsigned long gp;
    /** tp register state */
    unsigned long tp;
    /** t0 register state */
    unsigned long t0;
    /** t1 register state */
    unsigned long t1;
    /** t2 register state */
    unsigned long t2;
    /** s0 register state */
    unsigned long s0;
    /** s1 register state */
    unsigned long s1;
    /** a0 register state */
    unsigned long a0;
    /** a1 register state */
    unsigned long a1;
    /** a2 register state */
    unsigned long a2;
    /** a3 register state */
    unsigned long a3;
    /** a4 register state */
    unsigned long a4;
    /** a5 register state */
    unsigned long a5;
    /** a6 register state */
    unsigned long a6;
    /** a7 register state */
    unsigned long a7;
    /** s2 register state */
    unsigned long s2;
    /** s3 register state */
    unsigned long s3;
    /** s4 register state */
    unsigned long s4;
    /** s5 register state */
    unsigned long s5;
    /** s6 register state */
    unsigned long s6;
    /** s7 register state */
    unsigned long s7;
    /** s8 register state */
    unsigned long s8;
    /** s9 register state */
    unsigned long s9;
    /** s10 register state */
    unsigned long s10;
    /** s11 register state */
    unsigned long s11;
    /** t3 register state */
    unsigned long t3;
    /** t4 register state */
    unsigned long t4;
    /** t5 register state */
    unsigned long t5;
    /** t6 register state */
    unsigned long t6;
    /** mepc register state */
    unsigned long mepc;
    /** mstatus register state */
    unsigned long mstatus;
};

#endif /* #ifndef __M_TRAP_H__ */
