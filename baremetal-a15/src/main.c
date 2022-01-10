/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>

void platform_init(void)
{
	console_init();
}

int main(void)
{
	platform_init();
	bm_printf("enter main\n");
	return 0;
}
