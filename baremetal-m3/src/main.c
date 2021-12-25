/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <sys_ctrl.h>
#include <mpu.h>
#include <nvic.h>

int global_variable_data = 0x11223344;
int global_variable_bss1;

void printf_test(void)
{
	unsigned int test = 0x12345678;
	unsigned char test_u8 = 0x88;

	global_variable_bss1 = 0x3333;
	bm_printf("Enter _main!\n");
	bm_printf_value_u32("This is test value:", test);
	bm_printf_value_u32("The golbal variable is :", global_variable_data);
	bm_printf_value_u32("The golbal variable is :", global_variable_bss1);
	bm_printf_value_u8("unsigned char print test :", test_u8);
	bm_printf_value_u8("unsigned char print test :", test_u8);
}

void platform_init(void)
{
	console_init();
	sys_ctrl_init();
	mpu_init();
	nvic_init();
}

int main(void)
{
	platform_init();
	printf_test();
	return 0;
}
