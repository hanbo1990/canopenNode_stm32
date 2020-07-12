/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-03     hanbo       the first version
 */
#ifndef APPLICATIONS_HW_OPERATION_IWDT_H_
#define APPLICATIONS_HW_OPERATION_IWDT_H_

rt_err_t iwdt_init(void);
rt_err_t iwdt_feed(void);

#endif /* APPLICATIONS_HW_OPERATION_IWDT_H_ */
