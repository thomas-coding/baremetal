/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <apbuart.h>

#define MAX_DIGIT_BITS 11  /* 8 char for number, 2 for '0x' and 1 for '\n' */
static const char HEX_TABLE[] = {'0', '1', '2', '3', '4', '5', '6', '7',
								'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void bm_printf(char *s)
{
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

static void to_hex(unsigned int value, char msg[])
{
	int i = MAX_DIGIT_BITS - 1;

	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void bm_printf_hex(unsigned int value)
{
	char value_str[MAX_DIGIT_BITS];

	for (int i = 0; i < MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex(value, value_str);
	bm_printf(value_str);
}

void bm_printf_value(char *s, unsigned int value)
{
	bm_printf(s);
	bm_printf_hex(value);
}

void console_init(void)
{
	uart_init();
}
