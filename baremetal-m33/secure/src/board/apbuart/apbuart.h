/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef APBUART_H
#define APBUART_H

typedef struct UART_t {
	volatile unsigned int DATA;
	volatile unsigned int STATE;
	volatile unsigned int CTRL;
	volatile unsigned int INTSTATUS;
	volatile unsigned int BAUDDIV;
} UART_t;

#define UART0_ADDR ((UART_t *)(0x40200000))

#define UART_CTRL_TX_EN (1 << 0)
#define UART_CTRL_RX_EN (1 << 1)
#define UART_CTRL_TX_INTR_EN (1 << 2)
#define UART_CTRL_RX_INTR_EN (1 << 3)

void uart_init(void);
void uart_putc(char c);
unsigned char uart_getc(void);

#endif