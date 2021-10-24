/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>

int main(void)
{
	unsigned int test = 0x12345678;

	console_init();
	bm_printf("Enter main!\n");
	bm_printf_value("This is test value:", test);
	return 0;
}
