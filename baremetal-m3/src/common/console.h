/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef CONSOLE_H
#define CONSOLE_H

void console_init(void);
void bm_printf(char *s);
void bm_printf_value(char *s, unsigned int value);

#endif