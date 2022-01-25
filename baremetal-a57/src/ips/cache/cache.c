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

/*  SCTLR_EL3 Get control Register */
uint64_t get_value_sctlr_el3(void)
{
	uint64_t val = 0;

	asm volatile("mrs %0, SCTLR_EL3" : "=r" (val));

	return val;
}

/* CSSELR_EL1 Cache Size Selection Register */
uint64_t get_value_csselr(void)
{
	uint64_t val = 0;

	asm volatile("mrs %0, CSSELR_EL1" : "=r" (val));

	return val;
}

/* CSSELR_EL1 Cache Size Selection Register */
void set_value_csselr(uint64_t val)
{
	asm volatile("msr CSSELR_EL1, %0" : : "r" (val));
	asm volatile("isb");
}

/* CCSIDR_EL1 Get cache ways/words/sets
 * http://8.210.111.180/share/doc/arm/cortex-a/DDI0488H_cortex_a57_mpcore_trm.pdf
 * 4.3.22 Cache Size ID Register, EL1
 */
uint64_t get_value_ccsidr(void)
{
	uint64_t val = 0;

	asm volatile("mrs %0, CCSIDR_EL1" : "=r" (val));

	return val;
}

void get_cache_info(void)
{
	/* 0x000000000A200023, include L1 and L2 cache, no L3 cache*/
	bm_printf_value_u64("CLIDR:", get_value_clidr());

	/* 0x0000000000C50838, bit2 for cache enable, default is disabled */
	bm_printf_value_u64("SCTLR_EL3:", get_value_sctlr_el3());

	/* L1 i-cache info */
	set_value_csselr(1);
	/* 0x00000000201FE012 : 48K, 64 bytes/line, 3 ways, 256 sets, support read-allocation */
	bm_printf_value_u64("L1 i-cache CCSIDR_EL1:", get_value_ccsidr());

	/* L1 d-cache info */
	set_value_csselr(0x0);
	/* 0x00000000701FE00A : 32K, 64 bytes/line, 2 ways, 256 sets, support read-allocation/write-allocation/write-back */
	bm_printf_value_u64("L1 d-cache CCSIDR_EL1:", get_value_ccsidr());

	/* L2 cache info */
	set_value_csselr(0x2);
	/* 0x0000000070FFE07A : 2048KB, 64 bytes/line, 16 ways, 2048 sets support read-allocation/write-allocation/write-back */
	bm_printf_value_u64("L2 cache ccsidr:", get_value_ccsidr());

}

void cache_test(void)
{
	get_cache_info();
}

/**
 * Initializes the Cache
 */
void cache_init(void)
{
	cache_test();
}
