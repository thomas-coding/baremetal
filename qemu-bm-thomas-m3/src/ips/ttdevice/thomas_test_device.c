/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <thomas_test_device.h>
#include <console.h>

/* QEMU Test device, REG2 = REG0 + REG1 */

/**
 * Initializes
 */
void thomas_test_device_init(void)
{
    TT_DEVICE_ADDR->REG0 = 0x22;
    TT_DEVICE_ADDR->REG1 = 0x33;
    bm_printf_value_u32("thomas test device REG0: ", TT_DEVICE_ADDR->REG0);
    bm_printf_value_u32("thomas test device REG1: ", TT_DEVICE_ADDR->REG1);
    bm_printf_value_u32("thomas test device REG2: ", TT_DEVICE_ADDR->REG2);
}
