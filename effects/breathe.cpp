/*
 * breath.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

void update_breathe()
{
	static uint8_t intensity;
	static uint8_t breathe_tick;
	if (frames & 15)
		return;
	else
		breathe_tick = (breathe_tick + 1) & 63;
	intensity = sin_table[breathe_tick];
	for (rgb_color* led = colors; (led != colors_end); led++)
	{
		*led = (rgb_color
				)
				{ intensity, 0, 0 };
	}
}
