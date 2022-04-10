/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <thomas_test_device.h>
#include <console.h>
#include <nvic.h>
#include <sys_ctrl.h>

/* QEMU Test device, REG2 = REG0 + REG1 */
/* It has irq , number 15 */

void thomas_test_device_reg_test(void)
{
    TT_DEVICE_ADDR->REG0 = 0x22;
    TT_DEVICE_ADDR->REG1 = 0x33;
    bm_printf_value_u32("thomas test device REG0: ", TT_DEVICE_ADDR->REG0);
    bm_printf_value_u32("thomas test device REG1: ", TT_DEVICE_ADDR->REG1);
    bm_printf_value_u32("thomas test device REG2: ", TT_DEVICE_ADDR->REG2);
}

/* Only support 0-31 irq */
#define THOMAS_TEST_DEVICET_IRQ 15

void thomas_test_device_irq_handler(void)
{
    bm_printf("Enter thomas_test_device_irq_handler!\n");
    /* clear interrupt */
    TT_DEVICE_ADDR->REG4 = 0xa5;
}

void thomas_test_device_irq_test(void)
{
    bm_printf("thomas_test_device_irq_test\n");

    /* Enable this interrupt */
    NVIC->ISER[(((uint32_t)THOMAS_TEST_DEVICET_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)THOMAS_TEST_DEVICET_IRQ) & 0x1FUL));

    /* Get the vectors table offset , now is 0x00000000 */
    uint32_t *vectors = (uint32_t *)SCB->VTOR;

    vectors[(uint32_t)(THOMAS_TEST_DEVICET_IRQ) + 16] = (uint32_t)thomas_test_device_irq_handler;

    /* trigger interrupt */
    TT_DEVICE_ADDR->REG3 = 0xa5;
    //NVIC->ISPR[(((uint32_t)TEST_NORNAL_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_NORNAL_IRQ) & 0x1FUL));
}

/**
 * Initializes
 */
void thomas_test_device_init(void)
{
    thomas_test_device_reg_test();
    thomas_test_device_irq_test();
}
