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

#define LIGHT_NAME(id) _CONCAT(light_, id)
#define LIGHT_DEV(id)  (&LIGHT_NAME(id))
#define LIGHT_DEVICE_DEFINE(id, connector)                           \
				MINODE_LIGHT_DEVICE_DEFINE(LIGHT_NAME(id), _CONCAT(A, id),   \
				STRINGIFY(id),                                               \
				light_on_level_change)

static struct mb_image lighting[] = {

  MB_IMAGE({ 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 }),

  MB_IMAGE({ 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 1, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 }),

  MB_IMAGE({ 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 1, 1, 1, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0 }),

  MB_IMAGE({ 0, 0, 0, 0, 0 },
					 { 0, 1, 1, 1, 0 },
					 { 0, 1, 1, 1, 0 },
					 { 0, 1, 1, 1, 0 },
					 { 0, 0, 0, 0, 0 }),

  MB_IMAGE({ 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 },
					 { 1, 1, 1, 1, 1 }),
};

void display_on(enum minode_light_level level)
{
  int index;
	struct mb_display *disp = mb_display_get();

  index = (int)level;
  if(index < MINODE_LIGHT_LEVEL_0 || index > MINODE_LIGHT_LEVEL_4) {
    return;
  }
  mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
      K_FOREVER, &lighting[index], 1);
}

void light_on_level_change(struct minode_light_device *dev,
        enum minode_light_level prev_level, enum minode_light_level new_level)
{
  const char *id = dev->user_data;
  printk("Light[%s] attached on %s level changed: prev_level=%d, new_level=%d.\n", id,
      dev->connector, prev_level, new_level);
  display_on(new_level);
}

LIGHT_DEVICE_DEFINE(0, A0);

void main(void)
{
  enum minode_light_level level;
	struct mb_display *disp = mb_display_get();

  printk("mi:node Light example starting.\n");

	minode_light_init(LIGHT_DEV(0));
  level = minode_light_get_level(LIGHT_DEV(0));
  display_on(level);
  minode_light_start_listening(LIGHT_DEV(0));
}
