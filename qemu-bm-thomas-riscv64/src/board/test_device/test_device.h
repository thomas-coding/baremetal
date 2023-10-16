/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef _TEST_DEVICE_H
#define _TEST_DEVICE_H

typedef struct TEST_DEVICE_t {
    volatile unsigned int REG0;
    volatile unsigned int REG1;
    volatile unsigned int REG2;
    volatile unsigned int REG3;
    volatile unsigned int REG4;
} TEST_DEVICE_t;

#define TRIGGER_INTERRUPT_MAGIC     0xa5
#define TEST_DEVICET_IRQ            100

#define TEST_DEVICE ((TEST_DEVICE_t *)(0X30000000))

void test_device_reg_test(void);
void test_device_irq_test(void);

#endif
