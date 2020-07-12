/*
 * File      : fal_cfg.h
 * This file is part of FAL (Flash Abstraction Layer) package
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>
#include <drv_common.h>

#define NOR_FLASH_DEV_NAME               "W25Q16"


#define ONCHIP_NAME                      "stm32_onchip"
#define ONCHIP_BL_NAME                   "stm32_onchip_bl"
#define ONCHIP_ROM_NAME                  "stm32_onchip_rom"
#define ONCHIP_APP_NAME                  "stm32_onchip_app"

#define FLASH_SIZE_GRANULARITY_16K      (16 * 1024)
#define FLASH_SIZE_GRANULARITY_64K      (64 * 1024)
#define FLASH_SIZE_GRANULARITY_128K     (128 * 1024)

#define FLASH_SIZE_BL                   (4 * FLASH_SIZE_GRANULARITY_16K)
#define FLASH_SIZE_ROM                  (1 * FLASH_SIZE_GRANULARITY_64K)
#define FLASH_SIZE_APP                  (3 * FLASH_SIZE_GRANULARITY_128K)

#define STM32_FLASH_START_ADRESS_16K    STM32_FLASH_START_ADRESS
#define STM32_FLASH_START_ADRESS_64K    (STM32_FLASH_START_ADRESS_16K + FLASH_SIZE_BL)
#define STM32_FLASH_START_ADRESS_128K   (STM32_FLASH_START_ADRESS_64K + FLASH_SIZE_ROM)

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32f4_onchip_flash;
//extern const struct fal_flash_dev stm32f4_onchip_flash_bl;
//extern const struct fal_flash_dev stm32f4_onchip_flash_rom;
//extern const struct fal_flash_dev stm32f4_onchip_flash_app;

extern struct fal_flash_dev nor_flash0;



/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32f4_onchip_flash,                                           \
    &nor_flash0,                                                     \
}

/**
//    &stm32f4_onchip_flash_bl,                                        \
//    &stm32f4_onchip_flash_rom,                                       \
//    &stm32f4_onchip_flash_app,                                       \
*/
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG

/* partition table */
#define FAL_PART_TABLE                                                                 \
{                                                                                      \
    {FAL_PART_MAGIC_WORD,        "bl",          ONCHIP_NAME,         0,  128*1024, 0}, \
    {FAL_PART_MAGIC_WORD,       "app",          ONCHIP_NAME,  128*1024,  384*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "fwfactory",   NOR_FLASH_DEV_NAME,         0,  512*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "easyflash",   NOR_FLASH_DEV_NAME,  512*1024,  512*1024, 0}, \
    {FAL_PART_MAGIC_WORD,  "download",   NOR_FLASH_DEV_NAME, 1024*1024, 1024*1024, 0}, \
}

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
