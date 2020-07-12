/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#ifndef APPLICATIONS_BOARDCONFIG_HWCONFIG_H_
#define APPLICATIONS_BOARDCONFIG_HWCONFIG_H_

#include "drv_common.h"

/* LED */
#define LED_HEART_BEAT    GET_PIN(A, 6)
#define LED_1             GET_PIN(A, 7)

/* KEY */
#define KEY0              GET_PIN(E, 4)
#define KEY1              GET_PIN(E, 3)
#define KEY_WKUP          GET_PIN(A, 0)

/* OTHER */
#define DOG_TIME_OUT_SEC  10U

#endif /* APPLICATIONS_BOARDCONFIG_HWCONFIG_H_ */
