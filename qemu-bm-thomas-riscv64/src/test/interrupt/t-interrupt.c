/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "common.h"
#include "t-interrupt.h"
#include "test_device.h"

void interrupt_test(void)
{
    vs_printf("interrupt test: check if test device irq handle called\n");
    test_device_irq_test();
    mdelay(100);
}
