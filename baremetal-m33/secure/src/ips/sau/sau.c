/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <sau.h>

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
 * 0x0020_0000 - 0x003F_FFFF 2M NON-SECURE
 */
void sau_config_and_enable(void)
{
	/* Non-secure sram */
    SAU->RNR = 0;
    SAU->RBAR = 0x00200000;
    SAU->RLAR = 0x003FFFE1;

	/* Uart etc */
    SAU->RNR = 1;
    SAU->RBAR = 0x40100000;
    SAU->RLAR = 0x4fffffE1;

	/* Enable sau */
	SAU->CTRL = 0x1;
}

void sau_init(void)
{
	bm_printf("Enter sau init!\n");
    sau_config_and_enable();
	//dump_sau_reg();
}
