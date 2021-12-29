/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include <apbuart.h>

/**
 * Initializes the UART
 */
void uart_init(void)
{
	UART0_ADDR->BAUDDIV = 16;
	UART0_ADDR->CTRL = UART_CTRL_TX_EN | UART_CTRL_RX_EN | UART_CTRL_RX_INTR_EN;
}

/**
 * Output a char to the UART TX
 */
void uart_putc(char c)
{
	UART0_ADDR->DATA =  c;
}

// Get a character
unsigned char uart_getc(void)
{
    unsigned char my_ch;

    while ((UART0_ADDR->STATE & 2) == 0) // Wait if Receive
    {

    }

    my_ch = UART0_ADDR->DATA;

    // Convert CR to LF
    if (my_ch == '\r')
        my_ch = '\n';

    return (my_ch);
}

