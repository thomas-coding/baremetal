/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <gicv2.h>
#include <console.h>

void gicv2_dump_gicd(void)
{
	bm_printf_value_u32("GICD CTLR: ", GICDistributor->CTLR);
	bm_printf_value_u32("GICD TYPER: ", GICDistributor->TYPER);
}

void gicv2_dump_gicc(void)
{
	bm_printf_value_u32("GICC CTLR: ", GICInterface->CTLR);
	bm_printf_value_u32("GICC PMR: ", GICInterface->PMR);
	bm_printf_value_u32("GICC BPR: ", GICInterface->BPR);
	bm_printf_value_u32("GICC IAR: ", GICInterface->IAR);
}

void gicv2_test(void)
{

}

/**
 * Initializes the GICV2
 */
void gicv2_init(void)
{
	bm_printf("enter gicv2_init\n");
	gicv2_dump_gicd();
	gicv2_dump_gicc();
	gicv2_test();
}
