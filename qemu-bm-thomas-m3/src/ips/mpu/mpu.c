/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <mpu.h>
#include <console.h>

/*
	Ref config without DMA.
	S should be set for shareable. cache should be set for fast. buffer should not set for write-through safe.
	Memory region TEX C B S Memory type and attributes
	Flash memory 0b000 1 0 0 Normal memory, Non-shareable, write-through
	Internal SRAM 0b000 1 0 1 Normal memory, Shareable, write-through
	External SRAM 0b000 1 1 1 Normal memory, Shareable, write-back, write-allocate
	Peripherals 0b000 0 1 1 Device memory, Shareable
*/

void dump_mpu_reg(void)
{
	bm_printf_value_u32("MPU TYPE: ", MPU->TYPE);
	bm_printf_value_u32("MPU CTRL: ", MPU->CTRL);
	bm_printf_value_u32("MPU RNR: ", MPU->RNR);

	for (int i = 0; i < 8; i++) {
		bm_printf_value_u32("REGION NUMBER: ", i);
		MPU->RNR = i;
		bm_printf_value_u32("MPU RBAR: ", MPU->RBAR);
		bm_printf_value_u32("MPU RASR: ", MPU->RASR);
	}

}

/* 4M sram

 -------------
 1M
 -------------
 1M
 -------------
 1M privileged rw, un-priv ro
 -------------
 1M
 -------------
 ...
 ------------
 1G
 ------------

 */
void mpu_config(void)
{
	/* Region 0 */
	MPU->RNR = 0;
	MPU->RBAR = 0x20000000;
	MPU->RASR = 0x03030027; /* XN=0, AP=011(all allow), tex=0, s=0, c=1, b=1, srd=0, size=0x10011(1m), enable=1 */

	/* Region 1 */
	MPU->RNR = 1;
	MPU->RBAR = 0x20100000;
	MPU->RASR = 0x03030027; /* XN=0, AP=011(all allow), tex=0, s=0, c=1, b=1, srd=0, size=0x10011(1m), enable=1 */

	/* Region 2 */
	MPU->RNR = 2;
	MPU->RBAR = 0x20200000;
	MPU->RASR = 0x02030027; /* XN=0, AP=010(privileged rw, un-priv ro), tex=0, s=0, c=1, b=1, srd=0, size=0x10011(1m), enable=1 */

	/* Region 3 */
	MPU->RNR = 3;
	MPU->RBAR = 0x20300000;
	MPU->RASR = 0x03030027; /* XN=0, AP=011(all allow), tex=0, s=0, c=1, b=1, srd=0, size=0x10011(1m), enable=1 */

	/* Region 4 */
	MPU->RNR = 4;
	MPU->RBAR = 0x40000000;
	MPU->RASR = 0x1300003b; /* XN=1, AP=011(all allow), tex=0, s=0, c=0, b=0, srd=0, size=0x11101(1g), enable=1 */

	/* Region 0 4m flash*/
	MPU->RNR = 5;
	MPU->RBAR = 0x10000000;
	MPU->RASR = 0x0303002b; /* XN=0, AP=011(all allow), tex=0, s=0, c=1, b=1, srd=0, size=5b10101(4m), enable=1 */

	/* Enable MPU */
	asm volatile("dmb");
	MPU->CTRL = 0x5; /* PRIVDEFENA should set, otherwise when access uart that not defined in MPU, cause hard fault */
	asm volatile("dsb");
	asm volatile("isb");
}

void test_unprivileged_acess(void)
{
	/* Change to unprivileged */
	asm volatile("ldr		r0, =0x1");
	asm volatile("msr		control, r0");
	asm volatile("isb");

	/* Region4 allow uart access at unprivileged mode*/
	bm_printf_value_u32("0x20350000: ", *(volatile unsigned int *)(0x20350000));

	/* If address is 0x26000(in region 2), it will not allowed write, it will cause hard fault */
	*(volatile unsigned int *)(0x20360000) = 0x12345678;
	bm_printf_value_u32("0x20360000: ", *(volatile unsigned int *)(0x20360000));

	asm volatile("svc	#100");
}

void mpu_init(void)
{
	bm_printf("Enter mpu init!\n");
	mpu_config();
	test_unprivileged_acess();
	//dump_mpu_reg();
}
