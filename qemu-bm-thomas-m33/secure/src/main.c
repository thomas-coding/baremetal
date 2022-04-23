/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <sys_ctrl.h>
#include <mpu.h>
#include <nvic.h>
#include <systick.h>
#include <sau.h>
#include <mpc.h>
#include <ppc.h>

int global_variable_data = 0x11223344;
int global_variable_bss1;

void printf_test(void)
{
	unsigned int test = 0x12345678;
	unsigned char test_u8 = 0x88;

	global_variable_bss1 = 0x3333;
	bm_printf("Enter s_main!\n");
	bm_printf_value_u32("This is test value:", test);
	bm_printf_value_u32("The golbal variable is :", global_variable_data);
	bm_printf_value_u32("The golbal variable is :", global_variable_bss1);
	bm_printf_value_u8("unsigned char print test :", test_u8);
	bm_printf_value_u8("unsigned char print test :", test_u8);
}

void nsc_call_function(void)
{
	bm_printf("Enter nsc call!\n");
}

/* Refer README.md memory map define */
void call_ns_world(void)
{
	/* Set non-secure world vector base address */
	*(volatile unsigned int *)0xe002ed08=0x10200000;

	/* Set non-secure msp */
	asm volatile ("ldr r0, =0x10200000");
	asm volatile ("ldr r1, [r0]");
	asm volatile ("msr msp_ns, r1");

	/* Get non-secure entry */
	asm volatile ("ldr r0, =0x10200004");
	asm volatile ("ldr r1, [r0]");
	/* Bit0 set to 0, indicate enter non-secure state*/
	asm volatile ("bic r1,r1,#0x1");
	asm volatile ("bxns r1");
}

void platform_init(void)
{
	console_init();
	sys_ctrl_init();
	/* After sau init and before ppc init, can not used UART */
	//ppc_init();
	sau_init();
	//mpc_init();
	//mpu_init();
	nvic_init();
	systick_init();
}

int main(void)
{
	platform_init();
	printf_test();
	call_ns_world();
	return 0;
}
