/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <cache.h>
#include <console.h>
#include <type.h>

/* CLIDR Cache Level ID Register */
uint64_t get_value_clidr(void)
{
	uint64_t val = 0;

	asm volatile("mrs %0, CLIDR_EL1" : "=r" (val));

	return val;
}


void cache_test(void)
{
	/* 0x000000000A200023, include L1 and L2 cache, no L3 cache*/
	bm_printf_value_u64("CLIDR:", get_value_clidr());
}

/**
 * Initializes the Cache
 */
void cache_init(void)
{
	cache_test();
}
