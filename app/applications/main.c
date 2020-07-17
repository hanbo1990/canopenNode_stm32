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

rt_device_t dev = RT_NULL;
static struct rt_semaphore rx_sem;

rt_size_t data_size;

static rt_err_t usb_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);
    rt_kprintf("rx:%d...\n", size);
    data_size = size;
    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    char* ch;

    while (1)
    {
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);

        ch = (char*) rt_calloc(1, data_size + 1);

        if(NULL != ch){
            rt_device_read(dev, -1, ch, data_size);
            rt_kprintf("received:%s\n", ch);
            rt_free(ch);
            ch = NULL;
        } else {
            rt_kprintf("failed to malloc\n");
        }
    }
}

int main(void)
{
    rt_kprintf("System start up, current version is %s\n", APP_VERSION);

    (void) hw_init();
    (void) apppool_init();

    rt_thread_mdelay(2000);

    char buf[] = "hello rt-thread!\r\n";

    dev = rt_device_find("vcom");

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    if (dev){
        rt_kprintf("find vcom\n");
        rt_device_open(dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
    else{
        rt_kprintf("cannot find vcom\n");
        return -RT_ERROR;
    }

    rt_device_set_rx_indicate(dev, usb_input);

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    rt_thread_startup(thread);

    while (1)
    {
        rt_device_write(dev, 0, buf, rt_strlen(buf));
        rt_thread_mdelay(1000);
    }

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
