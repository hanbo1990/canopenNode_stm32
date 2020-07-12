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
#include <rtdbg.h>
#include "rthardware/iwdt.h"
#include "app_pool/events.h"

#define TASK_MONITOR_THREAD_PRIORITY         15
#define TASK_MONITOR_THREAD_STACK_SIZE       312
#define TASK_MONITOR_THREAD_TIMESLICE        5

static rt_thread_t tid = RT_NULL;

struct rt_event monitor_event;

static void thread_task_monitor_entry(void *parameter)
{
	rt_uint32_t e;

    while (rt_event_recv(&monitor_event, (TASK_MONITOR_EVENT_HEART_BEAT_ALIVE),
                         RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                         RT_WAITING_FOREVER, &e) == RT_EOK){
        // feed the dog when all tasks are active
    	iwdt_feed();
    }

}

int taskmonitor_start(void)
{
	rt_err_t result;

    result = rt_event_init(&monitor_event, "event", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("init event failed.\n");
        return -1;
    }

	tid = rt_thread_create("tskmon",
    					   thread_task_monitor_entry,
						   RT_NULL,
						   TASK_MONITOR_THREAD_STACK_SIZE,
						   TASK_MONITOR_THREAD_PRIORITY,
						   TASK_MONITOR_THREAD_TIMESLICE);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 1;
}
