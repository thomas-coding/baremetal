/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <apbuart.h>

typedef struct UART_t {
	volatile unsigned int DATA;
	volatile unsigned int STATE;
	volatile unsigned int CTRL;
	volatile unsigned int INTSTATUS;
	volatile unsigned int BAUDDIV;
} UART_t;

#define UART0_ADDR ((UART_t *)(0x40004000))

#define UART_CTRL_TX_EN (1 << 0)
#define UART_CTRL_RX_EN (1 << 1)

/**
 * Initializes the UART
 */
void uart_init(void)
{
	UART0_ADDR->BAUDDIV = 16;
	UART0_ADDR->CTRL = UART_CTRL_TX_EN;
}

/**
 * Output a char to the UART TX
 */
void uart_putc(char c)
{
	UART0_ADDR->DATA =  c;
}

