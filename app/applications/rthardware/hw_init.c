/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#include "gpio.h"
#include "hw_init.h"
#include "iwdt.h"
#include "button.h"
#include "file.h"

rt_err_t hw_init(void)
{
	gpio_init();

	button_start();

	iwdt_init();

//	file_init();

	return RT_EOK;
}

