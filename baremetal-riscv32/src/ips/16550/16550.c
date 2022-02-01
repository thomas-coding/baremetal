/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <16550.h>

/**
 * Initializes the UART
 */
void uart_init(void)
{
	//now use qemu, do not need init
}


/**
 * Output a char to the UART TX
 */
void uart_putc(char c)
{
	*(volatile unsigned int *)UART0_ADDR =  c;
}


