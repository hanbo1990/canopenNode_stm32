/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-05     hanbo       the first version
 */
#include <rtdbg.h>
#include <rtdevice.h>
#include "button.h"

#define BUTTON_DOWN_MS        50U
#define BUTTON_HOLD_MS        700U
#define BUTTON_SCAN_SPACE_MS  20U
#define BUTTON_LIST_MAX       10U

#define BUTTON_CALL(func, argv) \
    do { if ((func) != RT_NULL) func argv; } while (0)

struct button_manage {
    rt_uint8_t num;
    rt_timer_t timer;
    struct button_cfg *button_list[BUTTON_LIST_MAX];
};

static struct button_manage button_manage;

int button_register(struct button_cfg *button)
{
    if (button->press_logic_level == 0) {
        rt_pin_mode(button->pin, PIN_MODE_INPUT_PULLUP);
    } else {
        rt_pin_mode(button->pin, PIN_MODE_INPUT_PULLDOWN);
    }

    button->cnt = 0;
    button->event = BUTTON_EVENT_NONE;
    button_manage.button_list[button_manage.num++] = button;

    return 0;
}

static void button_scan(void *param)
{
    rt_uint8_t i;
    rt_uint16_t cnt_old;

    for (i = 0; i < button_manage.num; i++){
        cnt_old = button_manage.button_list[i]->cnt;

        if (rt_pin_read(button_manage.button_list[i]->pin) == button_manage.button_list[i]->press_logic_level){
            button_manage.button_list[i]->cnt ++;

            if (button_manage.button_list[i]->cnt == BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS){
                /* BUTTON_DOWN */
                LOG_D("BUTTON_DOWN");
                button_manage.button_list[i]->event = BUTTON_EVENT_CLICK_DOWN;
                BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            } else if (button_manage.button_list[i]->cnt == BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS){
                /* BUTTON_HOLD */
                LOG_D("BUTTON_HOLD");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD;
                BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            } else if (button_manage.button_list[i]->cnt > BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS){
                /* BUTTON_HOLD_CYC */
                LOG_D("BUTTON_HOLD_CYC");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD_CYC;
                if (button_manage.button_list[i]->hold_cyc_period &&
                    button_manage.button_list[i]->cnt % (button_manage.button_list[i]->hold_cyc_period / BUTTON_SCAN_SPACE_MS) == 0)
                    BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
        } else {
            button_manage.button_list[i]->cnt = 0;
            if (cnt_old >= BUTTON_DOWN_MS / BUTTON_SCAN_SPACE_MS && cnt_old < BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS){
                /* BUTTON_CLICK_UP */
                LOG_D("BUTTON_CLICK_UP");
                button_manage.button_list[i]->event = BUTTON_EVENT_CLICK_UP;
                BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            } else if (cnt_old >= BUTTON_HOLD_MS / BUTTON_SCAN_SPACE_MS){
                /* BUTTON_HOLD_UP */
                LOG_D("BUTTON_HOLD_UP");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD_UP;
                BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
        }
    }
}

int button_start()
{
    if (button_manage.timer != RT_NULL)
        return -1;

    button_manage.timer = rt_timer_create("btn_timer",
                                          button_scan,
                                          RT_NULL,
                                          RT_TICK_PER_SECOND * BUTTON_SCAN_SPACE_MS / 1000,
                                          RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    if (button_manage.timer != RT_NULL)
        rt_timer_start(button_manage.timer);

    return 0;
}
