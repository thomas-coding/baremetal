/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <nvic.h>
#include <console.h>
#include <sys_ctrl.h>

#define NVIC_USER_IRQ_OFFSET          16

/* Set 1 to disable irq, the same as "cpsid i" */
void set_PRIMASK(uint32_t priMask)
{
	asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}

uint32_t get_PRIMASK(void)
{
	uint32_t result;

	asm volatile ("MRS %0, primask" : "=r" (result));
	return result;
}

/* Priority based on mask, priority high(0 is highest) then this can be process */
void set_BASEPRI(uint32_t basePri)
{
	asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}

uint32_t get_BASEPRI(void)
{
	uint32_t result;

	asm volatile ("MRS %0, basepri" : "=r" (result));
	return result;
}



void dump_nvic_reg(void)
{
	for (int i = 0; i < 1; i++) {
		bm_printf_value_u32("NVIC ISER: ", NVIC->ISER[i]);
		bm_printf_value_u32("NVIC ICER: ", NVIC->ICER[i]);
		bm_printf_value_u32("NVIC ISPR: ", NVIC->ISPR[i]);
		bm_printf_value_u32("NVIC ICPR: ", NVIC->ICPR[i]);
		bm_printf_value_u32("NVIC IABR: ", NVIC->IABR[i]);
	}

	for (int i = 0; i < 32; i++)
		bm_printf_value_u32("NVIC IP: ", NVIC->IP[i]);

}


#define TEST_PROMPT_IRQ_LOW_PROMPT 11
#define TEST_PROMPT_IRQ_HIGH_PROMPT 12

/* This the low priority isr, when it set higher priority to pending ,
 * This function will be prompted, high priority isr will be called,
 * After high priority isr finish, this function will continue running,
 * After this function finish, thread mode will be continue running.
 * nvic_interrupt_prompt_test --> nvic_interrupt_prompt_test_irq_low --> nvic_interrupt_prompt_test_irq_high --> nvic_interrupt_prompt_test_irq_low --> nvic_interrupt_prompt_test
 */
void nvic_interrupt_prompt_test_irq_low(void)
{
	bm_printf("Enter nvic_interrupt_prompt_test_irq_low!\n");

	/* Set high interrupt to pending for test */
	NVIC->ISPR[(((uint32_t)TEST_PROMPT_IRQ_HIGH_PROMPT) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_PROMPT_IRQ_HIGH_PROMPT) & 0x1FUL));

	asm volatile("dsb");
	asm volatile("isb");

	/* If high prompt irq priority is high, it this log is delay after irq high run */
	bm_printf("after pendingg high prompt!\n");
}

void nvic_interrupt_prompt_test_irq_high(void)
{
	bm_printf("Enter nvic_interrupt_prompt_test_irq_high!\n");
}


void nvic_interrupt_prompt_test(void)
{
	/* set base pri, below this can not process*/
	set_BASEPRI(0x66);

	/* Enable this interrupt */
	NVIC->ISER[(((uint32_t)TEST_PROMPT_IRQ_LOW_PROMPT) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_PROMPT_IRQ_LOW_PROMPT) & 0x1FUL));
	NVIC->ISER[(((uint32_t)TEST_PROMPT_IRQ_HIGH_PROMPT) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_PROMPT_IRQ_HIGH_PROMPT) & 0x1FUL));

	/* Get the vectors table offset , now is 0x00000000 */
	uint32_t *vectors = (uint32_t *)SCB->VTOR;

	vectors[(uint32_t)(TEST_PROMPT_IRQ_LOW_PROMPT) + NVIC_USER_IRQ_OFFSET] = (uint32_t)nvic_interrupt_prompt_test_irq_low;
	vectors[(uint32_t)(TEST_PROMPT_IRQ_HIGH_PROMPT) + NVIC_USER_IRQ_OFFSET] = (uint32_t)nvic_interrupt_prompt_test_irq_high;

	/* Set low interrupt to lowest priority, but greater then base pri */
	NVIC->IP[((uint32_t)TEST_PROMPT_IRQ_LOW_PROMPT)] = (uint8_t)(0x55);
	NVIC->IP[((uint32_t)TEST_PROMPT_IRQ_HIGH_PROMPT)] = (uint8_t)(0x11);

	/* Set low interrupt to pending for test */
	NVIC->ISPR[(((uint32_t)TEST_PROMPT_IRQ_LOW_PROMPT) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_PROMPT_IRQ_LOW_PROMPT) & 0x1FUL));
}

void nvic_normal_interrupt_test_irq(void)
{
	/* Check psr is 0x100001a, exception number is 26 (16 + 10) */
	bm_printf("Enter nvic_normal_interrupt_test_irq!\n");
}

/* Only support 0-31 irq */
#define TEST_NORNAL_IRQ 10
void nvic_normal_interrupt_test(void)
{
	bm_printf("nvic_normal_interrupt_test\n");

	/* Enable this interrupt */
	NVIC->ISER[(((uint32_t)TEST_NORNAL_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_NORNAL_IRQ) & 0x1FUL));

	/* Get the vectors table offset , now is 0x00000000 */
	uint32_t *vectors = (uint32_t *)SCB->VTOR;

	vectors[(uint32_t)(TEST_NORNAL_IRQ) + NVIC_USER_IRQ_OFFSET] = (uint32_t)nvic_normal_interrupt_test_irq;

	/* Set this interrupt to pending for test */
	NVIC->ISPR[(((uint32_t)TEST_NORNAL_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)TEST_NORNAL_IRQ) & 0x1FUL));
}

void nvic_test(void)
{
	nvic_normal_interrupt_test();
	nvic_interrupt_prompt_test();
}

void nvic_init(void)
{
	bm_printf("Enter nvic init!\n");
	nvic_test();
	//dump_nvic_reg();
}
