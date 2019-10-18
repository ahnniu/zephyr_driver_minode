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

#define SOUND_SENSOR_NAME(id) _CONCAT(sound_, id)
#define SOUND_SENSOR_DEV(id)  (&SOUND_SENSOR_NAME(id))
#define SOUND_SENSOR_DEVICE_DEFINE(id, connector)                           \
				MINODE_SOUND_DEVICE_DEFINE(SOUND_SENSOR_NAME(id), _CONCAT(A, id),   \
				STRINGIFY(id),                                                      \
				sound_on_noise_detect)

static struct mb_image lighting[] = {

  MB_IMAGE({ 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 }),

  MB_IMAGE({ 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 }),
};

void display_on(int is_noise_detected)
{
  int index;
	struct mb_display *disp = mb_display_get();

  index = is_noise_detected;
  if(index < 0 || index > 1) {
    return;
  }

  mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
      K_SECONDS(1), &lighting[index], 1);
}

void sound_on_noise_detect(struct minode_sound_device *dev)
{
  const char *id = dev->user_data;
  printk("Light[%s] attached on %s noise detected.\n", id,
      dev->connector);
  display_on(1);
}

SOUND_SENSOR_DEVICE_DEFINE(0, A0);

void main(void)
{
	struct mb_display *disp = mb_display_get();

  printk("mi:node Sound sensor example starting.\n");
	minode_sound_init(SOUND_SENSOR_DEV(0));
  display_on(minode_sound_is_in_noise(SOUND_SENSOR_DEV(0)));
  minode_sound_start_listening(SOUND_SENSOR_DEV(0));
}
