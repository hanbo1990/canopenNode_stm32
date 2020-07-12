/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */

#include <rtthread.h>
#include <stdbool.h>
#include <rtdbg.h>
#include <rtdevice.h>

#include "rthardware/hwconfig.h"
#include "app_pool/events.h"

#define THREAD_PRIORITY         20
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

extern struct rt_event monitor_event;

static void thread_heartbeat_entry(void *parameter)
{
	bool outStatus = true;
    while (1)
    {
    	rt_event_send(&monitor_event, TASK_MONITOR_EVENT_HEART_BEAT_ALIVE);
    	outStatus = !outStatus;
    	rt_pin_write(LED_HEART_BEAT, outStatus);
		rt_thread_mdelay(2000);
    }
}

int heartbeat_start(void)
{
    tid1 = rt_thread_create("heartbeat",
    						thread_heartbeat_entry,
							RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    return 1;
}
