/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>

#include <display/mb_display.h>
#include <minode.h>

#define DHT_SENSOR_NAME(id) _CONCAT(dht_, id)
#define DHT_SENSOR_DEV(id)  (&DHT_SENSOR_NAME(id))
#define DHT_SENSOR_DEVICE_DEFINE(id, connector)                             \
				MINODE_DHT_DEVICE_DEFINE(DHT_SENSOR_NAME(id), _CONCAT(A, id),       \
				STRINGIFY(id),                                                      \
				on_new_sampling)


void on_new_sampling(struct minode_dht_device *dev)
{
  const char *id = dev->user_data;
  struct mb_display *disp = mb_display_get();
  struct sensor_value temp_data;

  minode_dht_ambient_temp_get(dev, &temp_data);
  printk("DHT11[%s] attached on %s new sampling - ambient_temp: %d\n", id,
      dev->connector, temp_data.val1);

  mb_display_print(disp, MB_DISPLAY_MODE_SCROLL, K_SECONDS(2), "%d", temp_data.val1);
}

DHT_SENSOR_DEVICE_DEFINE(0, A0);

void main(void)
{
	struct mb_display *disp = mb_display_get();

  printk("mi:node DHT11 sensor example starting.\n");
	minode_dht_init(DHT_SENSOR_DEV(0));
  minode_dht_start_sampling(DHT_SENSOR_DEV(0), 5000);
}
