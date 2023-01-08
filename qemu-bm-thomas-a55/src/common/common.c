/*
 * Contains the common function.
 *
 * Author: Kang Zhigang <Zhigang.Kang@verisilicon.com>
 *
 * Copyright (C) 2021 VeriSilicon Microelectronics (Shanghai) Co., Ltd.
 *
 */

#include "common.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

extern void *verify_callback[][2];
static uint32_t verify_item_num;

static void print_test_info(void)
{
	char c = 0;
	uint8_t i = 0;

	vs_printf("\n*******************************************\n");
	vs_printf("please input test module ID:\n");
	while (1) {
		if ((uint32_t)(verify_callback[i][0] == 0))
			break;

		c = (i > 9 ? (i + 87) : (i + 48));
		vs_printf("%c -- %s\n", c, verify_callback[i][1]);
		i++;
	}

	verify_item_num = i;

	vs_printf("> ");
}

void vs_verify_loop(void)
{
	uint8_t c = 0;
	uint8_t item_id = 0;
	pfunc pfunc_callback = 0;

	while (1) {
		print_test_info();

		c = vs_getc();
		vs_putc(c);

		if (c >= '0' && c <= '9') {
			item_id = c - 48;
		} else if (c >= 'A' && c <= 'Z') {
			item_id = c - 55;
		} else if (c >= 'a' && c <= 'z') {
			item_id = c - 87;
		} else {
			vs_printf("The input is wrong, try again!\n");
			continue;
		}

		if (item_id < verify_item_num) {
			vs_printf("\n******* %s run Start *******\n",
					verify_callback[item_id][1]);

			pfunc_callback = verify_callback[item_id][0];
			if (pfunc_callback != 0)
				pfunc_callback();

			vs_printf("\n******* %s run End *******\n",
					verify_callback[item_id][1]);
		} else {
			vs_printf("\n\nThere is no such verify item!\n");
		}
	}
}

