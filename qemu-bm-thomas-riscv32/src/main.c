/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "common.h"

extern void tiny_uart_console(void);

void *verify_callback[][2] = {
	{ (void *)tiny_uart_console, "Tiny console" },
	{ 0, 0 },
};

void sys_init(void)
{
    console_init();
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
