/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#define METAL_MSTATUS_MIE_SHIFT 8
#define METAL_MSTATUS_MPP_M     3
#define METAL_MSTATUS_MPP_SHIFT 11

#define METAL_MTVEC_MODE_MASK   3

#define REG_SAVED_NUMBER  (32 + 2)
#define REG_SAVED_SIZE (REG_SAVED_NUMBER * 4)

.macro portSAVE_BaseReg
    /* Make room for the registers. */
    addi	sp, sp, -REG_SAVED_SIZE
    sw  x1,  4(sp)		/* x1(ra)		Return address */
                                                    /* x2(sp) ***** Should be save ouside this macro */
    sw  x3,  12(sp)		/* x3(gp)		Global pointer */
    sw  x4,  16(sp)		/* x4(tp)		Thread pointer */
    sw  x5,  20(sp)		/* x5(t0)		Temporary register */
    sw  x6,  24(sp)		/* x6(t1)		Temporary register*/
    sw  x7,  28(sp)		/* x7(t2)		Temporary register */
    sw  x8,  32(sp)		/* x8(s0/fp)	Saved register/Frame pointer */
    sw  x9,  36(sp)		/* x9(s1)		Saved register */
    sw  x10, 40(sp)		/* x10(a0)		Function argument */
    sw  x11, 44(sp)		/* x11(a1)		Function argument */
    sw  x12, 48(sp)		/* x12(a2)		Function argument */
    sw  x13, 52(sp)		/* x13(a3)		Function argument */
    sw  x14, 56(sp)		/* x14(a4)		Function argument */
    sw  x15, 60(sp)		/* x15(a5)		Function argument */
#ifndef __riscv_32e
    sw  x16, 64(sp)		/* x16(a6)		Function arguments */
    sw  x17, 68(sp)		/* x17(a7)		Function arguments */
    sw  x18, 72(sp)		/* x18(s2)		Saved register */
    sw  x19, 76(sp)		/* x19(s3)		Saved register */
    sw  x20, 80(sp)		/* x20(s4)		Saved register */
    sw  x21, 84(sp)		/* x21(s5)		Saved register */
    sw  x22, 88(sp)		/* x22(s6)		Saved register */
    sw  x23, 92(sp)		/* x23(s7)		Saved register */
    sw  x24, 96(sp)		/* x24(s8)		Saved register */
    sw  x25, 100(sp)	/* x25(s9)		Saved register */
    sw  x26, 104(sp)	/* x26(s10)		Saved register */
    sw  x27, 108(sp)	/* x27(s11)		Saved register */
    sw  x28, 112(sp)	/* x28(t3)		Temporary register */
    sw  x29, 116(sp)	/* x29(t4)		Temporary register */
    sw  x30, 120(sp)	/* x30(t5)		Temporary register */
    sw  x31, 124(sp)	/* x31(t6)		Temporary register */
#endif /* __riscv_32e */
    /* Save mcause, mepc & mstatus state */
    csrr a4, mepc
    csrr a5, mstatus		/* Required for MPIE bit. */
    sw a4, 128(sp)
    sw a5, 132(sp)
    .endm

.macro portRESTORE_BaseReg
    /* Restore mepc & mstatus state */
    lw  t0, 128(sp)
    lw  t1, 132(sp)
    csrw	mepc, t0
    csrw	mstatus, t1

    lw  x1,  4(sp)		/* x1(ra)		Return address */
                                                    /* x2(sp) ***** Should be save ouside this macro */
    lw  x3,  12(sp)		/* x3(gp)		Global pointer */
    lw  x4,  16(sp)		/* x4(tp)		Thread pointer */
    lw  x5,  20(sp)		/* x5(t0)		Temporary register */
    lw  x6,  24(sp)		/* x6(t1)		Temporary register*/
    lw  x7,  28(sp)		/* x7(t2)		Temporary register */
    lw  x8,  32(sp)		/* x8(s0/fp)	Saved register/Frame pointer */
    lw  x9,  36(sp)		/* x9(s1)		Saved register */
    lw  x10, 40(sp)		/* x10(a0)		Function argument */
    lw  x11, 44(sp)		/* x11(a1)		Function argument */
    lw  x12, 48(sp)		/* x12(a2)		Function argument */
    lw  x13, 52(sp)		/* x13(a3)		Function argument */
    lw  x14, 56(sp)		/* x14(a4)		Function argument */
    lw  x15, 60(sp)		/* x15(a5)		Function argument */
#ifndef __riscv_32e
    lw  x16, 64(sp)		/* x16(a6)		Function arguments */
    lw  x17, 68(sp)		/* x17(a7)		Function arguments */
    lw  x18, 72(sp)		/* x18(s2)		Saved register */
    lw  x19, 76(sp)		/* x19(s3)		Saved register */
    lw  x20, 80(sp)		/* x20(s4)		Saved register */
    lw  x21, 84(sp)		/* x21(s5)		Saved register */
    lw  x22, 88(sp)		/* x22(s6)		Saved register */
    lw  x23, 92(sp)		/* x23(s7)		Saved register */
    lw  x24, 96(sp)		/* x24(s8)		Saved register */
    lw  x25, 100(sp)	/* x25(s9)		Saved register */
    lw  x26, 104(sp)	/* x26(s10)		Saved register */
    lw  x27, 108(sp)	/* x27(s11)		Saved register */
    lw  x28, 112(sp)	/* x28(t3)		Temporary register */
    lw  x29, 116(sp)	/* x29(t4)		Temporary register */
    lw  x30, 120(sp)	/* x30(t5)		Temporary register */
    lw  x31, 124(sp)	/* x31(t6)		Temporary register */
#endif /* __riscv_32e */
    .endm

/* void _metal_trap(int ecode)
 *
 * Trigger a machine-mode trap with exception code ecode
 */
.global _metal_trap
.type _metal_trap, @function

_metal_trap:

    /* Store the instruction which called _metal_trap in mepc */
    addi t0, ra, -1
    csrw mepc, t0

    /* Set mcause to the desired exception code */
    csrw mcause, a0

    /* Read mstatus */
    csrr t0, mstatus

    /* Set MIE=0 */
    li t1, -1
    xori t1, t1, METAL_MSTATUS_MIE_SHIFT
    and t0, t0, t1

    /* Set MPP=M */
    li t1, METAL_MSTATUS_MPP_M
    slli t1, t1, METAL_MSTATUS_MPP_SHIFT
    or t0, t0, t1

    /* Write mstatus */
    csrw mstatus, t0

    /* Read mtvec */
    csrr t0, mtvec

    /*
     * Mask the mtvec MODE bits
     * Exceptions always jump to mtvec.BASE regradless of the vectoring mode.
     */
    andi t0, t0, METAL_MTVEC_MODE_MASK

    /* Jump to mtvec */
    jr t0


/*
 * For sanity's sake we set up an early trap vector that just does nothing.
 * If you end up here then there's a bug in the early boot code somewhere.
 */
.section .text.metal.init.trapvec
.global early_trap_vector
.align 2
early_trap_vector:
    .cfi_startproc
    csrr t0, mcause
    csrr t1, mepc
    csrr t2, mtval
    j early_trap_vector
    .cfi_endproc


.section .text.metal.init.trapvec
.global m_trap_vector
.align 2
m_trap_vector:
    .cfi_startproc
    /* We do not know if this is an ASYNC or SYNC
     * If ASYNC, it is a normal interrupt
     *  and the stack pointer is assumed good.
     * else (SYNC)
     *  We could be here due to a bus fault.
     */
    csrw	mscratch, t0
    csrr	t0, mcause
    blt  	t0, x0, handle_interrupt

handle_exception:
    /* mscratch = old t0
     * t0 = mcause
     * mcause = small number 0..16
     *  0 Instruction address misaligned
     *  1 Instruction access fault
     *  2 Illegal instruction
     *  3 Breakpoint
     *  4 Load address misaligned
     *  5 Load access fault
     *  6 Store/AMO address misaligned
     *  7 Store/AMO access fault
     *  8 Environment call from U-mode
     *  9 Environment call from S-mode
     *  10 Reserved
     *  11 Environment call from M-mode
     *  12 Instruction page fault
     *  13 Load page fault
     *  14 Reserved
     *  15 Store/AMO page fault
     *  ≥16 Reserved
     *
     * if( mcause between 8 and 11  ) we are good - ecall
     * else: problem
     */

    addi	t0, t0, -8
    blt		t0, x0, is_exception /* mcause < 8, must be fault */
    addi	t0, t0, -4
    blt		t0, x0, environment_switch

/* TODO: Exception need print some info */
is_exception:
    j       .
    mret

/* Now only has machine mode */
environment_switch:
    j       .
    mret

/*
 * Save cortext
 * Call interrupt handler
 * Restore cortext
 */
handle_interrupt:
    portSAVE_BaseReg
    /* a4 = mepc
     * a5 = mstatus
     */

    /* Store the value of sp when the interrupt occur */
    addi t0, sp, REG_SAVED_SIZE
    sw  t0, 8(sp)

    /* Call C routine */
    add	a0, sp, zero
    call	trap_handler

    portRESTORE_BaseReg
    lw  x2, 8(sp)
    mret

    .cfi_endproc
