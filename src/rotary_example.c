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

#define ROTARY_NAME(id) _CONCAT(rotary_, id)
#define ROTARY_DEV(id)  (&ROTARY_NAME(id))
#define ROTARY_DEVICE_DEFINE(id, connector)                           \
				MINODE_ROTARY_DEVICE_DEFINE(ROTARY_NAME(id), _CONCAT(A, id),   \
				STRINGIFY(id),                                               \
				rotary_on_level_change)

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

void display_on(enum minode_rotary_level level)
{
  int index;
	struct mb_display *disp = mb_display_get();

  index = (int)level;
  if(index < MINODE_ROTARY_LEVEL_0 || index > MINODE_ROTARY_LEVEL_9) {
    return;
  }
  index = index / 2;
  mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
      K_FOREVER, &lighting[index], 1);
}

void rotary_on_level_change(struct minode_rotary_device *dev,
        enum minode_rotary_level prev_level, enum minode_rotary_level new_level)
{
  const char *id = dev->user_data;
  printk("Light[%s] attached on %s level changed: prev_level=%d, new_level=%d.\n", id,
      dev->connector, prev_level, new_level);
  display_on(new_level);
}

ROTARY_DEVICE_DEFINE(0, A0);

void main(void)
{
  enum minode_rotary_level level;
	struct mb_display *disp = mb_display_get();

  printk("mi:node Rotary example starting.\n");
	minode_rotary_init(ROTARY_DEV(0));
  level = minode_rotary_get(ROTARY_DEV(0));
  display_on(level);
  minode_rotary_start_listening(ROTARY_DEV(0));
}
