/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-06     hanbo       the first version
 */

#include <fal.h>
#include <dfs_fs.h>

#define DBG_SECTION_NAME               "file"
#define DBG_LEVEL                      DBG_INFO
#include <rtdbg.h>

#define FS_PARTITION_NAME              "easyflash"
#define W25Q_SPI_DEVICE_NAME     "spi10"

//static void test_ext_flash(void)
//{
//    struct rt_spi_device *spi_dev_w25q;
//    char name[RT_NAME_MAX];
//    rt_uint8_t w25x_read_id = 0x90;
//    rt_uint8_t id[5] = {0};
//
//    rt_strncpy(name, W25Q_SPI_DEVICE_NAME, RT_NAME_MAX);
//    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
//    if (!spi_dev_w25q)
//    {
//        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
//    } else {
//        /* config spi */
//        {
//            struct rt_spi_configuration cfg;
//            cfg.data_width = 8;
//            cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
//            cfg.max_hz = 50 * 1000 * 1000; /* 50M */
//            rt_spi_configure(spi_dev_w25q, &cfg);
//        }
//
//        /* 方式1：使用 rt_spi_send_then_recv()发送命令读取ID */
//        rt_err_t err= rt_spi_send_then_recv(spi_dev_w25q, &w25x_read_id, 1, id, 5);
//        if(RT_EOK == err)
//            rt_kprintf("use rt_spi_send_then_recv() read w25q ID is:%x%x%x%x%x\n",
//                    id[0], id[1], id[2], id[3], id[4]);
//        else
//            rt_kprintf("read failed");
//
//        /* 方式2：使用 rt_spi_transfer_message()发送命令读取ID */
//        struct rt_spi_message msg1, msg2;
//
//        msg1.send_buf   = &w25x_read_id;
//        msg1.recv_buf   = RT_NULL;
//        msg1.length     = 1;
//        msg1.cs_take    = 1;
//        msg1.cs_release = 0;
//        msg1.next       = &msg2;
//
//        msg2.send_buf   = RT_NULL;
//        msg2.recv_buf   = id;
//        msg2.length     = 5;
//        msg2.cs_take    = 0;
//        msg2.cs_release = 1;
//        msg2.next       = RT_NULL;
//
//        rt_spi_transfer_message(spi_dev_w25q, &msg1);
//        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);
//    }
//
//}

int file_init(void)
{
//    test_ext_flash();

    fal_init();

    if (!fal_mtd_nor_device_create("easyflash") ||
        !fal_mtd_nor_device_create("download"))
    {
        LOG_E("Can't create a mtd device on '%s' partition.", FS_PARTITION_NAME);
    } else {
        LOG_I("create %s partition successfully", FS_PARTITION_NAME);

        // create partion if not exist
        if (dfs_mount("easyflash", "/", "lfs", 0, 0) == 0)
        {
            LOG_I("Filesystem initialized!");
        }
        else
        {
            dfs_mkfs("lfs", FS_PARTITION_NAME);
//
            if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) == 0)
            {
                LOG_I("Filesystem initialized!");
            }
            else
            {
                LOG_E("Failed to initialize filesystem!");
            }
        }
    }

    return 0;

}

INIT_ENV_EXPORT(file_init);
