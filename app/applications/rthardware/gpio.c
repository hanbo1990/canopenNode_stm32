/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#include <board.h>
#include <rtdevice.h>
#include "gpio.h"
#include "hwconfig.h"

void gpio_init(void)
{
	rt_pin_mode(LED_HEART_BEAT, PIN_MODE_OUTPUT);
}
