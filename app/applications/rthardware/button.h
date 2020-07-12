/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-05     hanbo       the first version
 */
#ifndef APPLICATIONS_RTHARDWARE_BUTTON_H_
#define APPLICATIONS_RTHARDWARE_BUTTON_H_

#include <rtthread.h>

/**
 *
 */
enum button_event {
    BUTTON_EVENT_CLICK_DOWN,//!< BUTTON_EVENT_CLICK_DOWN
    BUTTON_EVENT_CLICK_UP,  //!< BUTTON_EVENT_CLICK_UP
    BUTTON_EVENT_HOLD,      //!< BUTTON_EVENT_HOLD
    BUTTON_EVENT_HOLD_CYC,  //!< BUTTON_EVENT_HOLD_CYC
    BUTTON_EVENT_HOLD_UP,   //!< BUTTON_EVENT_HOLD_UP
    BUTTON_EVENT_NONE       //!< BUTTON_EVENT_NONE
};

/**
 *
 * @param
 */
typedef void (*button_event_callback)(void*);

/**
 *
 */
struct button_cfg {
    /* logic level when press down */
    rt_uint8_t  press_logic_level;

    /* Count to support long press scan */
    rt_uint16_t cnt;

    /* Button press event will be reported each period the button is pressed,
     * if set to 10, each 10 ms, event will be reported*/
    rt_uint16_t hold_cyc_period;

    /* Pin number assigned to the button */
    rt_uint16_t pin;

    /* Event triggered in the button, will passed to callback */
    enum button_event event;

    /* Callback function to the button press event */
    button_event_callback cb;
};

/**
 *
 * @param button
 * @return
 */
int button_register(struct button_cfg *button);

/**
 *
 * @return
 */
int button_start(void);

#endif /* APPLICATIONS_RTHARDWARE_BUTTON_H_ */
