/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-05     hanbo       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdbool.h>
#include "rthardware/button.h"
#include "rthardware/hwconfig.h"

#define KEY_PRESS_VALUE 0U

void toggle_led(struct button_cfg *button)
{
    static bool outStatus = true;

    switch (button->event){
    case BUTTON_EVENT_CLICK_DOWN:
        outStatus = !outStatus;
        rt_pin_write(LED_1, outStatus);
        break;

    default:
        ;
    }
}

void btnexample_start(void)
{
    static struct button_cfg button = {0};

    rt_pin_mode(LED_1, PIN_MODE_OUTPUT);
    rt_pin_write(LED_1, true);

    button.press_logic_level = KEY_PRESS_VALUE;
    button.hold_cyc_period = 100;
    button.cb = (button_event_callback)toggle_led;
    button.pin = KEY1;

    button_register(&button);
}
