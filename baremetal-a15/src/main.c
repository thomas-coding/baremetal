/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <mmu.h>
#include <cache.h>

void platform_init(void)
{
	console_init();
	mmu_init();
	cache_init();
}

unsigned int golbal_variable_initialized1 = 0x88;
unsigned int golbal_variable_initialized2 = 0x77;
unsigned int golbal_variable_not_init;
void data_and_bss_test()
{
	golbal_variable_initialized1++;
	golbal_variable_initialized2--;
	bm_printf_value_u32("golbal_variable_not_init before:",golbal_variable_not_init);
	golbal_variable_not_init = 0x99;
	bm_printf_value_u32("golbal_variable_initialized1:",golbal_variable_initialized1);
	bm_printf_value_u32("golbal_variable_initialized2:",golbal_variable_initialized2);
	bm_printf_value_u32("golbal_variable_not_init after:",golbal_variable_not_init);
}

int main(void)
{
	platform_init();
	data_and_bss_test();
	bm_printf("enter main\n");
	return 0;
}
