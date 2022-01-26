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

static inline uint32_t current_el(void)
{
	uint32_t el = 0;

	asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
	return el >> 2;
}

static uint32_t get_sctlr(void)
{
	uint32_t el = 0, val = 0;

	el = current_el();
	if (el == 1)
		asm volatile("mrs %0, sctlr_el1" : "=r" (val) : : "cc");
	else if (el == 2)
		asm volatile("mrs %0, sctlr_el2" : "=r" (val) : : "cc");
	else
		asm volatile("mrs %0, sctlr_el3" : "=r" (val) : : "cc");

	return val;
}

static void set_sctlr(uint32_t val)
{
	uint32_t el = 0;

	el = current_el();
	if (el == 1)
		asm volatile("msr sctlr_el1, %0" : : "r" (val) : "cc");
	else if (el == 2)
		asm volatile("msr sctlr_el2, %0" : : "r" (val) : "cc");
	else
		asm volatile("msr sctlr_el3, %0" : : "r" (val) : "cc");

	asm volatile("isb");
	asm volatile("dsb sy");
}

extern void asm_invalidate_icache_all(void);
void invalidate_icache_all(void)
{
	asm_invalidate_icache_all();
}

void icache_enable(void)
{
	invalidate_icache_all();
	set_sctlr(get_sctlr() | CR_I);
}

void icache_disable(void)
{
	set_sctlr(get_sctlr() & ~CR_I);
}

int icache_status(void)
{
	return (get_sctlr() & CR_I) != 0;
}

extern void __asm_invalidate_dcache_all(void);
extern void __asm_flush_dcache_all(void);
/*
 * Performs a invalidation of the entire data cache at all levels
 */
void invalidate_dcache_all(void)
{
	__asm_invalidate_dcache_all();
}

void dcache_enable(void)
{
	/* The data cache is not active unless the mmu is enabled */
	if (!(get_sctlr() & CR_M)) {
		invalidate_dcache_all();
	}

	set_sctlr(get_sctlr() | CR_C);
}

void flush_dcache_all(void)
{
	__asm_flush_dcache_all();
}

void dcache_disable(void)
{
	/* if cache isn't enabled no need to disable */
	if (!(get_sctlr() & CR_C))
		return;

	flush_dcache_all();
	invalidate_dcache_all();
}

int dcache_status(void)
{
	return (get_sctlr() & CR_C) != 0;
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

	icache_enable();

	dcache_enable();
}
