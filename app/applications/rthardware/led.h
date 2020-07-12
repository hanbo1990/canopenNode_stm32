///*
// * Copyright (c) 2006-2020, RT-Thread Development Team
// *
// * SPDX-License-Identifier: Apache-2.0
// *
// * Change Logs:
// * Date           Author       Notes
// * 2020-07-05     hanbo       the first version
// */
//#ifndef APPLICATIONS_RTHARDWARE_LED_H_
//#define APPLICATIONS_RTHARDWARE_LED_H_
//
///**
// *
// */
//enum led_mode {
//    LED_MODE_ON,
//    LED_MODE_OFF,
//    LED_MODE_TOGGLE,
//    LED_MODE_BLINK,
//    LED_MODE_BLINK_A_WILE,
//    BUTTON_EVENT_NONE
//};
//
///**
// *
// */
//struct led_cfg {
//    /* logic level when led is on */
//    rt_uint8_t  on_logic_level;
//
//    rt_uint8_t  blink_cnt;
//
//    rt_uint16_t  interval_in_sec;
//
//    rt_bool_t  current_val;
//
//    /* Pin number assigned to the button */
//    rt_uint16_t pin;
//
//    rt_timer_t timer;
//
//    /* Event triggered in the button, will passed to callback */
//    enum led_mode mode;
//};
//
///**
// * The new led behavior will overwrite the old one.
// * @param led
// * @return
// */
//int led_register(struct led_cfg *button);
//
///**
// *
// * @return
// */
//int led_start(void);
//
//
//#endif /* APPLICATIONS_RTHARDWARE_LED_H_ */
