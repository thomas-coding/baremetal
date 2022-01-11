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

unsigned int golbal_variable_initialized1 = 0x88;
unsigned int golbal_variable_initialized2 = 0x77;
void data_and_bss_test()
{
	golbal_variable_initialized1++;
	golbal_variable_initialized2--;
	bm_printf_value_u32("golbal_variable_initialized1:",golbal_variable_initialized1);
	bm_printf_value_u32("golbal_variable_initialized2:",golbal_variable_initialized2);
}

int main(void)
{
	platform_init();
	data_and_bss_test();
	bm_printf("enter main\n");
	return 0;
}
