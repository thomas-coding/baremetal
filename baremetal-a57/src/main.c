/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <cache.h>
#include <type.h>

unsigned int golbal_variable_initialized1 = 0x88;
unsigned int golbal_variable_initialized2 = 0x77;
unsigned int golbal_variable_not_init;
void data_and_bss_test()
{
	golbal_variable_initialized1++;
	golbal_variable_initialized2--;
	bm_printf_value_u32("golbal_variable_not_init before:", golbal_variable_not_init);
	golbal_variable_not_init = 0x99;
	bm_printf_value_u32("golbal_variable_initialized1:", golbal_variable_initialized1);
	bm_printf_value_u32("golbal_variable_initialized2:", golbal_variable_initialized2);
	bm_printf_value_u32("golbal_variable_not_init after:", golbal_variable_not_init);

}

void printf_test(void)
{
	uint8_t data_8 = 0x66;
	uint16_t data_16 = 0x7777;
	uint32_t data_32 = 0x88888888;
	uint64_t data_64 = 0x9999999999999999;

	bm_printf_value_u8("data_8:", data_8);
	bm_printf_value_u16("data_16:", data_16);
	bm_printf_value_u32("data_32:", data_32);
	bm_printf_value_u64("data_64:", data_64);
}

void platform_init(void)
{
	console_init();
	cache_init();
}

int main(void)
{
	platform_init();
	bm_printf("enter main\n");
	data_and_bss_test();
	return 0;
}
