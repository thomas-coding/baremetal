/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <mmu.h>
#include <cache.h>
//#include <gicv2.h>
#include <interrupt.h>
#include <misc.h>
#include <generic_timer.h>
#include <thomas_test_device.h>
#include <smp.h>

void platform_init(void)
{
	console_init();
	mmu_init();
	cache_init();
	//gicv2_init();
	gic_init();
	misc_init();
	generic_timer_init();
	thomas_test_device_init();
	smp_init();
}

void svc_function_8(void)
{
	bm_printf("svc_function_8\n");
}

void usr_mode_test(void)
{
	/* Change to usr mode */
	asm volatile("msr	CPSR_c, #0x10" );

	bm_printf("now in usr mode\n");

	/* Use svc call into svc mode */
	asm volatile("svc #8" );

	bm_printf("return from svc, still in usr mode\n");
}

/* NOTICE: This test should modify qemu source code first.
 * hw/arm/virt.c virt_flash_map function, put all flash to non-secure.
 * default 0x00000000-0x04000000 is configed as secure.
 * When we call smc, change to non-secre, then we fetch instruction from flash will be fail.
 */
void smc_test(void)
{
	bm_printf("\nsmc_test start\n");

	asm volatile("smc 0");
	bm_printf("\nNow in non-secure world ...\n");
	asm volatile("smc 0");
	bm_printf("\nNow in secure world ...\n");

	bm_printf("\n\nsmc_test\n\t\t - - - PASS\n");
	bm_printf("\nsmc_test end\n");
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
	//smc_test();
	//usr_mode_test();
	smp_test();
	return 0;
}
