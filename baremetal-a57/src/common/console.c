/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <pl011.h>
#include <console.h>

#define U8_MAX_DIGIT_BITS 6  /* 2 char for number, 2 for '0x' and 1 for '\n', last 0 for end */
#define U16_MAX_DIGIT_BITS 8  /* 4 char for number, 2 for '0x' and 1 for '\n', last 0 for end */
#define U32_MAX_DIGIT_BITS 12  /* 8 char for number, 2 for '0x' and 1 for '\n', last 0 for end */
#define U64_MAX_DIGIT_BITS 20  /* 16 char for number, 2 for '0x' and 1 for '\n', last 0 for end */

static const char HEX_TABLE[] = {'0', '1', '2', '3', '4', '5', '6', '7',
								'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void bm_printf(char *s)
{
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

static void to_hex_u8(uint8_t value, char msg[])
{
	int i = U8_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void to_hex_u16(uint16_t value, char msg[])
{
	int i = U16_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void to_hex_u32(uint32_t value, char msg[])
{
	int i = U32_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void to_hex_u64(uint64_t value, char msg[])
{
	int i = U64_MAX_DIGIT_BITS - 1;

	msg[i--] = 0;
	msg[i--] = '\n';
	for (; i > 1; i--, value >>= 4)
		msg[i] = HEX_TABLE[value & 0xF];
	msg[i--] = 'x';
	msg[i--] = '0';
}

static void bm_printf_hex_u8(uint8_t value)
{
	char value_str[U8_MAX_DIGIT_BITS];

	for (int i = 0; i < U8_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u8(value, value_str);
	bm_printf(value_str);
}

static void bm_printf_hex_u16(uint16_t value)
{
	char value_str[U16_MAX_DIGIT_BITS];

	for (int i = 0; i < U16_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u16(value, value_str);
	bm_printf(value_str);
}

static void bm_printf_hex_u32(uint32_t value)
{
	char value_str[U32_MAX_DIGIT_BITS];

	for (int i = 0; i < U32_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u32(value, value_str);
	bm_printf(value_str);
}

static void bm_printf_hex_u64(uint64_t value)
{
	char value_str[U64_MAX_DIGIT_BITS];

	for (int i = 0; i < U64_MAX_DIGIT_BITS; i++)
		value_str[i] = 0;

	to_hex_u64(value, value_str);
	bm_printf(value_str);
}

void bm_printf_value_u8(char *s, uint8_t value)
{
	bm_printf(s);
	bm_printf_hex_u8(value);
}

void bm_printf_value_u16(char *s, uint16_t value)
{
	bm_printf(s);
	bm_printf_hex_u16(value);
}

void bm_printf_value_u32(char *s, uint32_t value)
{
	bm_printf(s);
	bm_printf_hex_u32(value);
}

void bm_printf_value_u64(char *s, uint64_t value)
{
	bm_printf(s);
	bm_printf_hex_u64(value);
}

void console_init(void)
{
	uart_init();
}
