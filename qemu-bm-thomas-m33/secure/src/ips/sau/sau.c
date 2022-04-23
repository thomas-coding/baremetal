/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <sau.h>
#include <ppc.h>

void dump_sau_reg(void)
{
	int sau_region_number = SAU->TYPE;
	
	bm_printf_value_u32("sau CTRL: ", SAU->CTRL);
	bm_printf_value_u32("sau TYPE: ", SAU->TYPE);
	for(int i = 0; i < sau_region_number; i++) {
		SAU->RNR = i;
		bm_printf_value_u32("sau RNR: ", SAU->RNR);
		bm_printf_value_u32("sau RBAR: ", SAU->RBAR);
		bm_printf_value_u32("sau RLAR: ", SAU->RLAR);
	}
	bm_printf_value_u32("sau SFSR: ", SAU->SFSR);		
	bm_printf_value_u32("sau SFAR: ", SAU->SFAR);
}

/*
*  0x00000000 .. 0x0fffffff : Reserved
*  0x10000000 .. 0x101fffff : Secure Flash(2M)
	*  0x10000000 .. 0x100fffff : Secure code(1M)
	*  0x10100000 .. 0x101fffff : Non-Secure-callable code(1M)
*  0x10200000 .. 0x103fffff : Non-Secure Flash(2M)
*  0x20000000 .. 0x201fffff : Secure SRAM(2M)
*  0x20200000 .. 0x203fffff : Non-Secure SRAM(2M)
*  0x40000000 .. 0x40000fff : APB UART(4K)
*  0x50000000 .. 0x50000fff : Thomas Test Device(4K)
*/
void sau_config_and_enable(void)
{
	/* Non-secure flash */
	SAU->RNR = 0;
	SAU->RBAR = 0x10200000;
	SAU->RLAR = 0x103FFFE1;

	/* Non-secure sram */
	SAU->RNR = 1;
	SAU->RBAR = 0x20200000;
	SAU->RLAR = 0x203FFFE1;

	/* Uart etc */
	SAU->RNR = 2;
	SAU->RBAR = 0x40000000;
	SAU->RLAR = 0x4fffffE1;

	/* Non-secure callable flash */
	SAU->RNR = 3;
	SAU->RBAR = 0x10100000;
	SAU->RLAR = 0x101FFFE3;

	/* Enable sau */
	SAU->CTRL = 0x1;
}

void sau_init(void)
{
	bm_printf("Enter sau init!\n");
	sau_config_and_enable();
	//dump_sau_reg();
}
