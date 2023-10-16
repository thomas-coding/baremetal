/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <test_device.h>
#include <console.h>
#include <interrupt.h>
#include "common.h"

/* QEMU Test device, REG2 = REG0 + REG1 */

void test_device_reg_test(void)
{
    TEST_DEVICE->REG0 = 0x22;
    TEST_DEVICE->REG1 = 0x33;
    vs_printf("test device REG0:0x%x ", TEST_DEVICE->REG0);
    vs_printf("test device REG1:0x%x ", TEST_DEVICE->REG1);
    vs_printf("test device RGE0 + REG1 = REG2:0x%x ", TEST_DEVICE->REG2);
}

void test_device_irq_handler(int irq, void *parm)
{
    vs_printf("test device irq handler called!\n");
    /* clear interrupt */
    TEST_DEVICE->REG4 = TRIGGER_INTERRUPT_MAGIC;
}

void test_device_irq_test(void)
{
    request_irq(TEST_DEVICET_IRQ, test_device_irq_handler, NULL);
    /* trigger interrupt */
    TEST_DEVICE->REG3 = TRIGGER_INTERRUPT_MAGIC;
}
