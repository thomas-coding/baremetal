/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef GENERIC_TIMER_H
#define GENERIC_TIMER_H

#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

#ifndef uint64_t
typedef unsigned long long int uint64_t;
#endif

/* Running on QEMU virt, I don't know freq, suitable for my machine */
#define PERIPH_CLK		60000000

#define G_TIMER_ENABLE	(1 << 0)
#define G_TIMER_MASK	(1 << 1)
#define G_TIMER_IRQ	(1 << 2)

/* From include/hw/arm/virt.h */
#define ARCH_TIMER_VIRT_IRQ   (11 + 16)
#define ARCH_TIMER_S_EL1_IRQ  (13 + 16)
#define ARCH_TIMER_NS_EL1_IRQ (14 + 16)
#define ARCH_TIMER_NS_EL2_IRQ (10 + 16)

void generic_timer_init(void);
void gtimer_udelay(uint32_t us);
void gtimer_mdelay(uint32_t ms);
void gtimer_sdelay(uint32_t s);

#endif
