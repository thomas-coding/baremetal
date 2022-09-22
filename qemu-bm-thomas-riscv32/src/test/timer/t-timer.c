/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Core-Local Interruptor (CLINT) driver
 *
 */

#include "common.h"
#include "t-timer.h"

void timer_test(void)
{
    uint64_t tick = get_ticks();

    vs_printf("get tick:0x%llx\n", tick);

    vs_printf("before delay 3s\n");
    delay(3);
    vs_printf("after delay 3s\n");

    vs_printf("start timer for 2s, check if interrupt handler called\n");

    timer_start_ms(2000);
    delay(3);
}
