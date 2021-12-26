/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <systick.h>
#include <console.h>
#include <sys_ctrl.h>

void dump_systick_reg(void)
{
	bm_printf_value_u32("systick CTRL: ", SysTick->CTRL);
	bm_printf_value_u32("systick LOAD: ", SysTick->LOAD);
	bm_printf_value_u32("systick VAL: ", SysTick->VAL);
	bm_printf_value_u32("systick CALIB: ", SysTick->CALIB);
}

void systick_isr(void)
{
	/* Disable systick */
	SysTick->CTRL = 0x0;
	asm volatile("dsb");
	asm volatile("isb");

	bm_printf("systick_isr called!\n");
}

void systick_interrupt_test(void)
{

	/* Get the vectors table offset , now is 0x00000000 */
	uint32_t *vectors = (uint32_t *)SCB->VTOR;

	/* 15 is systick location in exception vectors table */
	vectors[15] = (uint32_t)systick_isr;

	/* 0xFFFFFF+1 clock cycle, count down form 0xFFFFFF to 0 */
	SysTick->LOAD = 0xFFFFFF;

	/* Clear current value to 0, it will load from reload register */
	SysTick->VAL = 0;

	/* Use processor clock source, assert interrupt, enable */
	SysTick->CTRL = 0x7;
}


void systick_test(void)
{
	uint32_t before, after;

	/* 0xFFFFFF+1 clock cycle, count down form 0xFFFFFF to 0 */
	SysTick->LOAD = 0xFFFFFF;

	/* Clear current value to 0, it will load from reload register */
	SysTick->VAL = 0;

	/* Use processor clock source, not assert interrupt, enable */
	SysTick->CTRL = 0x5;

	asm volatile("dsb");
	asm volatile("isb");

	before = SysTick->VAL;

	for (int i = 0; i < 1000; i++)
		asm volatile("nop");

	after = SysTick->VAL;

	bm_printf_value_u32("systick before nop: ", before);
	bm_printf_value_u32("systick after nop: ", after);
	bm_printf_value_u32("used clock cycles: ", before - after);

	/* Disable systick */
	SysTick->CTRL = 0x0;

}

void systick_init(void)
{
	bm_printf("Enter systick init!\n");
	systick_test();
	systick_interrupt_test();
	dump_systick_reg();
}
