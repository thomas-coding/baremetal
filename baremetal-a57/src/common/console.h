/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef CONSOLE_H
#define CONSOLE_H
#include <type.h>

void console_init(void);
void bm_printf(char *s);
void bm_printf_value_u8(char *s, uint8_t value);
void bm_printf_value_u16(char *s, uint16_t value);
void bm_printf_value_u32(char *s, uint32_t value);
void bm_printf_value_u64(char *s, uint64_t value);

#endif