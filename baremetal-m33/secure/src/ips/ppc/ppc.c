/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <console.h>
#include <ppc.h>

void ppc_config(void)
{
	struct spctrl_def* spctrl = CMSDK_SPCTRL;
    /* Grant non-secure access for APB peripherals on EXP1 */
	spctrl->apbnsppcexp1 = 0xffffffff;
}

void ppc_init(void)
{
	//bm_printf("Enter ppc init!\n");
    ppc_config();
}
