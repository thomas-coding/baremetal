/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>

int global_variable_data = 0x11223344;
int global_variable_bss1;

void printf_test(void)
{
	unsigned int test = 0x12345678;

	global_variable_bss1 = 0x3333;
	console_init();
	bm_printf("Enter _main!\n");
	bm_printf_value("This is test value:", test);
	bm_printf_value("The golbal variable is :", global_variable_data);
	bm_printf_value("The golbal variable is :", global_variable_bss1);
}

int main(void)
{
	printf_test();
	return 0;
}
