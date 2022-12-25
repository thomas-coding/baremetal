/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "devices.h"
#include "common.h"

int main(void)
{
	int count=0;
	count++;

	devices_init();

	vs_printf("enter main\n");

	while(1) {};
	return 0;
}
