/*
 * Copyright (c) 2021-2031, Jinping Wu. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#include "common.h"

void sys_init(void)
{
    console_init();
    vs_printf("%s\n", __DATE__);
}

int main(void)
{
    sys_init();
    return 0;
}
