/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#include "app_pool.h"
#include "background/task_monitor.h"
#include "background/heartbeat.h"
#include "background/button_example.h"

int apppool_init(void)
{


	(void) heartbeat_start();
	btnexample_start();
	(void) taskmonitor_start();

	return 1;
}
