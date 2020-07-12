/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-05     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "app_pool/app_pool.h"
#include "rthardware/hw_init.h"

int main(void)
{
    LOG_D("System start up");

    (void) hw_init();
    (void) apppool_init();

    return RT_EOK;
}
