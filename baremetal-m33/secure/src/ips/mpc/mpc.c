/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <mpc.h>

void dump_mpc_reg(void)
{
	bm_printf_value_u32("SRAM0_MPC MPC CTRL: ", SRAM0_MPC->CTRL);
	bm_printf_value_u32("SRAM0_MPC MPC BLK_MAX: ", SRAM0_MPC->BLK_MAX);
	bm_printf_value_u32("SRAM0_MPC MPC BLK_CFG: ", SRAM0_MPC->BLK_CFG);
}

void mpc_config_and_enable(void)
{
         SRAM0_MPC->CTRL &= ~(1UL << 8);         /* clear auto increment */
		for(int i = 64; i < 128; i++) {
			//bm_printf_value_u32("111 SRAM0_MPC MPC index: ", i);
         	SRAM0_MPC->BLK_IDX = i;               /* write LUT index */
         	SRAM0_MPC->BLK_LUT = 0xffffffff;     /* configure blocks is non-secure */
		}
}


void mpc_init(void)
{
	//bm_printf("Enter mpc init!\n");
    mpc_config_and_enable();
	//dump_mpc_reg();
}
