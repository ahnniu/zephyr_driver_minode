/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/gpio.h>
#include <device.h>

#include <display/mb_display.h>
#include <minode_connector.h>
#include <minode_switch.h>

#define SWITCH_NAME(id) _CONCAT(switch_, id)
#define SWITCH_DEV(id)  (&SWITCH_NAME(id))
#define IS_SWITCH_ON(id) minode_switch_is_on(SWITCH_DEV(id))
#define SWITCH_DEVICE_DEFINE(id, connector)                          \
				MINODE_SWITCH_DEVICE_DEFINE(SWITCH_NAME(id), _CONCAT(A, id), \
				STRINGIFY(id),                                               \
				switch_event_on, switch_event_off)

static struct mb_image smiley = MB_IMAGE({ 0, 1, 0, 1, 0 },
					 { 0, 1, 0, 1, 0 },
					 { 0, 0, 0, 0, 0 },
					 { 1, 0, 0, 0, 1 },
					 { 0, 1, 1, 1, 0 });

void display_on(const char *str)
{
	struct mb_display *disp = mb_display_get();
	mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_FOREVER, str);
}

void display_off()
{
	struct mb_display *disp = mb_display_get();
	mb_display_stop(disp);
}

void switch_event_on(struct minode_switch_device *dev)
{
	const char *id = dev->user_data;
	printk("Switch[%s] on.\n", id);
	display_on(id);
}

void switch_event_off(struct minode_switch_device *dev)
{
	const char *id = dev->user_data;
	printk("Switch[%s] off.\n", id);
	display_off();
}

SWITCH_DEVICE_DEFINE(0, A0);
SWITCH_DEVICE_DEFINE(1, A1);

void main(void)
{
	struct mb_display *disp = mb_display_get();

	minode_switch_init(SWITCH_DEV(0));
	minode_switch_init(SWITCH_DEV(1));

	if (IS_SWITCH_ON(0)) {
		display_on(SWITCH_DEV(0)->user_data);
	} else if (IS_SWITCH_ON(1)) {
		display_on(SWITCH_DEV(1)->user_data);
	} else {
		mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
					K_FOREVER, &smiley, 1);
	}
}
