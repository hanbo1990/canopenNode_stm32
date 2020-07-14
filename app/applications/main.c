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
#include <rtdbg.h>
#include "app_pool/app_pool.h"
#include "rthardware/hw_init.h"
#include "fal.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#define APP_VERSION "v0.0.0"

int main(void)
{
    rt_kprintf("System start up, current version is %s\n", APP_VERSION);

    (void) hw_init();
    (void) apppool_init();

    return RT_EOK;
}

/**
 * Function    ota_app_vtor_reconfig
 * Description Set Vector Table base location to the start addr of app(RT_APP_PART_ADDR).
*/
static int ota_app_vtor_reconfig(void)
{
    #define NVIC_VTOR_MASK   0x3FFFFF80
    /* Set the Vector Table base location by user application firmware definition */
    SCB->VTOR = RT_APP_PART_ADDR & NVIC_VTOR_MASK;

    return 0;
}
INIT_BOARD_EXPORT(ota_app_vtor_reconfig);
