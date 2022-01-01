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

#define TZ_START_NS 0x100000
/* Non-secure function type declaration */
typedef void nsfunc(void);

void set_mps_ns(uint32_t topOfMainStack)
{
  asm volatile ("MSR msp_ns, %0" : : "r" (topOfMainStack) : );
}

/*
 * NOTE: Non-secure image must already be present in memory before running
 *       this function
 */
void nonsecure_init(void)
{
	/* SCB_NS.VTOR points to the Non-secure vector table base address */
	*(volatile unsigned int *)0xe002ed08=TZ_START_NS;

	/* 1st entry in the vector table is the Non-secure Main Stack Pointer */
	set_mps_ns(*((uint32_t *)TZ_START_NS));

	/* 2nd entry contains the address of the Non-secure Reset_Handler */
	nsfunc *ns_reset = ((nsfunc*)(*(((uint32_t *)TZ_START_NS)+1)));

	ns_reset();       /* Call the Non-secure Reset_Handler */
}

void platform_init(void)
{
	console_init();
	sys_ctrl_init();
	//mpu_init();
	nvic_init();
	systick_init();
}

int main(void)
{
	platform_init();
	printf_test();
	nonsecure_init();
	return 0;
}
