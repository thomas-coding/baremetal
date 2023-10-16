/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "common.h"
#include "devices.h"
#include "t-timer.h"
#include "t-interrupt.h"

extern void tiny_uart_console(void);

void *verify_callback[][2] = {
	{ (void *)tiny_uart_console, "Tiny console" },
	{ (void *)timer_test, "riscv generic timer test" },
	{ (void *)interrupt_test, "riscv external interrupt test" },
	{ 0, 0 },
};

void sys_init(void)
{
    devices_init();
    vs_printf("%s\n", __DATE__);
}

int main(void)
{
    sys_init();

	vs_printf("\nBare-metal test begin ...\n");

	vs_verify_loop();

	vs_printf("\nBare-metal test end\n");

    return 0;
}
