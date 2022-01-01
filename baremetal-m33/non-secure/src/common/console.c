/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <apbuart.h>
#include <nvic.h>
#include <sys_ctrl.h>

#define U32_MAX_DIGIT_BITS 12  /* 8 char for number, 2 for '0x' and 1 for '\n', last 0 for end */
#define U8_MAX_DIGIT_BITS 6  /* 2 char for number, 2 for '0x' and 1 for '\n', last 0 for end */
static const char HEX_TABLE[] = {'0', '1', '2', '3', '4', '5', '6', '7',
								'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int secure_flag_add = 0;

void bm_printf(char *s)
{

	if (secure_flag_add == 0) {
		uart_putc('[');
		uart_putc('n');
		uart_putc('s');
		uart_putc(']');
	}
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

static void to_hex_u32(unsigned int value, char msg[])
{
	int i = U32_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void to_hex_u8(unsigned char value, char msg[])
{
	int i = U8_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void bm_printf_hex_u32(unsigned int value)
{
	char value_str[U32_MAX_DIGIT_BITS];

	for (int i = 0; i < U32_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u32(value, value_str);
	bm_printf(value_str);
}

static void bm_printf_hex_u8(unsigned char value)
{
	char value_str[U8_MAX_DIGIT_BITS];

	for (int i = 0; i < U8_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u8(value, value_str);
	bm_printf(value_str);
}

void bm_printf_value_u32(char *s, unsigned int value)
{
	bm_printf(s);
	secure_flag_add = 1;
	bm_printf_hex_u32(value);
	secure_flag_add = 0;
}

void bm_printf_value_u8(char *s, unsigned char value)
{
	bm_printf(s);
	secure_flag_add = 1;
	bm_printf_hex_u8(value);
	secure_flag_add = 0;
}

void uart_rx_isr(void)
{
	/* Clear interrupt */
	UART0_ADDR->INTSTATUS = 0x3;
	bm_printf("Enter uart_rx_isr!\n");
}

#define UART_RX_IRQ 0
#define NVIC_USER_IRQ_OFFSET          16
void uart_receive_interrupt_test()
{
	bm_printf("Enter uart_receive_interrupt_test\n");

	/* Before test, Clear interrupt */
	UART0_ADDR->INTSTATUS = 0x3;
	NVIC->ICPR[(((uint32_t)UART_RX_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)UART_RX_IRQ) & 0x1FUL));

	/* Enable this interrupt */
	NVIC->ISER[(((uint32_t)UART_RX_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)UART_RX_IRQ) & 0x1FUL));

	/* Get the vectors table offset , now is 0x00000000 */
	uint32_t *vectors = (uint32_t *)SCB->VTOR;

	vectors[(uint32_t)(UART_RX_IRQ) + NVIC_USER_IRQ_OFFSET] = (uint32_t)uart_rx_isr;

	bm_printf("Enter uart_receive_interrupt_test, please enter char...\n");
	unsigned char my_ch = uart_getc();

	uart_putc(my_ch);
	bm_printf("\n");

	/* Disable this interrupt and clear vector */
	NVIC->ICER[(((uint32_t)UART_RX_IRQ) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)UART_RX_IRQ) & 0x1FUL));
	vectors[(uint32_t)(UART_RX_IRQ) + NVIC_USER_IRQ_OFFSET] = 0;

}

void uart_receive_test()
{
	bm_printf("Enter uart_test, please enter char...\n");
	unsigned char my_ch = uart_getc();
	bm_printf("uart_test after get char:\n");
	uart_putc(my_ch);
	bm_printf("\n");
}

void console_init(void)
{
	uart_init();
	/* Receive test is disabled default, can enable it for free */
	//uart_receive_test();
	//uart_receive_interrupt_test();
}
