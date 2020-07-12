///*
// * Copyright (c) 2006-2020, RT-Thread Development Team
// *
// * SPDX-License-Identifier: Apache-2.0
// *
// * Change Logs:
// * Date           Author       Notes
// * 2020-07-05     hanbo       the first version
// */
//
//#include "led.h"
//#include <rtdevice.h>
//
//#define LED_LIST_MAX 2U
//#define LED_TIME_NAME(N) ("led"#N)
//
//struct led_cfg *led_list[LED_LIST_MAX];
//
//void toggle_led(void* params)
//{
//    struct led_cfg *led = (struct led_cfg*) params;
//
//    led->current_val != led->current_val;
//    rt_pin_write(led->pin, led->current_val);
//}
//
//int create_toggle(struct led_cfg *led)
//{
//    if (led->timer != RT_NULL)
//        return -1;
//
//    button_manage.timer = rt_timer_create(LED_TIME_NAME(led->pin),
//                                          toggle_led,
//                                          (void*) led,
//                                          RT_TICK_PER_SECOND * led->interval_in_sec,
//                                          RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
//
//    if (button_manage.timer != RT_NULL)
//        rt_timer_start(button_manage.timer);
//
//    return 0;
//}
//
//
//
//int led_register(struct led_cfg *led)
//{
//    rt_pin_mode(led->pin, PIN_MODE_OUTPUT);
//
//    switch(led->mode){
//    case LED_MODE_ON:
//        rt_pin_write(led->pin, led->on_logic_level);
//        break;
//    case LED_MODE_OFF:
//        rt_pin_write(led->pin, !led->on_logic_level);
//        break;
//    case LED_MODE_TOGGLE:
//        create_toggle(led);
//        break;
//    case LED_MODE_BLINK:
//        create_toggle(led);
//
//    }
//    if(LED_MODE_ON led->mode)
//}
//
//
//
//
//int led_start(void);
