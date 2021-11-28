/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <sys_ctrl.h>
#include <console.h>

void dump_sys_ctrl_reg(void)
{
	bm_printf_value_u32("SYS CTRL CPUID: ", SCB->CPUID);
	bm_printf_value_u32("SYS CTRL ICSR: ", SCB->ICSR);
	bm_printf_value_u32("SYS CTRL VTOR: ", SCB->VTOR);
	bm_printf_value_u32("SYS CTRL AIRCR: ", SCB->AIRCR);
	bm_printf_value_u32("SYS CTRL SCR: ", SCB->SCR);
	bm_printf_value_u32("SYS CTRL CCR: ", SCB->CCR);
	for (int i = 0; i < 12; i++)
		bm_printf_value_u8("SYS CTRL SHP: ", SCB->SHP[i]);
	bm_printf_value_u32("SYS CTRL SHCSR: ", SCB->SHCSR);
	bm_printf_value_u32("SYS CTRL CFSR: ", SCB->CFSR);
	bm_printf_value_u32("SYS CTRL HFSR: ", SCB->HFSR);
	bm_printf_value_u32("SYS CTRL DFSR: ", SCB->DFSR);
	bm_printf_value_u32("SYS CTRL MMFAR: ", SCB->MMFAR);
	bm_printf_value_u32("SYS CTRL BFAR: ", SCB->BFAR);
	bm_printf_value_u32("SYS CTRL AFSR: ", SCB->AFSR);
	bm_printf_value_u32("SYS CTRL PFR[0]: ", SCB->PFR[0]);
	bm_printf_value_u32("SYS CTRL PFR[1]: ", SCB->PFR[1]);
	bm_printf_value_u32("SYS CTRL DFR: ", SCB->DFR);
	bm_printf_value_u32("SYS CTRL ADR: ", SCB->ADR);
	bm_printf_value_u32("SYS CTRL MMFR[0]: ", SCB->MMFR[0]);
	bm_printf_value_u32("SYS CTRL MMFR[1]: ", SCB->MMFR[1]);
	bm_printf_value_u32("SYS CTRL MMFR[2]: ", SCB->MMFR[2]);
	bm_printf_value_u32("SYS CTRL MMFR[3]: ", SCB->MMFR[3]);
	bm_printf_value_u32("SYS CTRL ISAR[0]: ", SCB->ISAR[0]);
	bm_printf_value_u32("SYS CTRL ISAR[1]: ", SCB->ISAR[1]);
	bm_printf_value_u32("SYS CTRL ISAR[2]: ", SCB->ISAR[2]);
	bm_printf_value_u32("SYS CTRL ISAR[3]: ", SCB->ISAR[3]);
	bm_printf_value_u32("SYS CTRL ISAR[4]: ", SCB->ISAR[4]);
	bm_printf_value_u32("SYS CTRL CPACR: ", SCB->CPACR);
}

void sys_ctrl_init(void)
{
	bm_printf("Enter sys ctrl init!\n");
	dump_sys_ctrl_reg();
}
