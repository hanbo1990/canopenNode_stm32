
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#include <rtdevice.h>
#include <rtdbg.h>
#include <board.h>
#include "hwconfig.h"
#include "iwdt.h"

#define WDT_DEVICE_NAME "wdt"

static rt_device_t wdg_dev;

rt_err_t iwdt_init(void)
{
	rt_err_t ret = RT_EOK;
	rt_uint32_t dog_timeout = DOG_TIME_OUT_SEC;

	wdg_dev = rt_device_find(WDT_DEVICE_NAME);
	if(!wdg_dev){
		LOG_D("Cannot find Watch dog");
		return 0;
	}

	ret = rt_device_init(wdg_dev);
	if(RT_EOK != ret){
		rt_kprintf("initialize %s failed!\n", WDT_DEVICE_NAME);
		return RT_ERROR;
	}

	ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &dog_timeout);
	if(RT_EOK != ret){
		rt_kprintf("set timeout for %s failed!\n", WDT_DEVICE_NAME);
		return RT_ERROR;
	}

	ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
	{
		rt_kprintf("start %s failed!\n", WDT_DEVICE_NAME);
		return -RT_ERROR;
	}

	return ret;
}

rt_err_t iwdt_feed(void)
{
	return rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}
