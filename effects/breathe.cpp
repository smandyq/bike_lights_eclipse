/*
 * breath.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

void update_breathe(uint8_t start, uint8_t end)
{
	static uint8_t intensity;
	static uint8_t breathe_tick;
	if (!(frames & 3))
		breathe_tick = (breathe_tick + 1) & 63;
	if(!((breathe_tick & 1) | (breathe_tick & 2)))
		intensity = 0;
	else
		intensity = sin_table[breathe_tick];
	rgb_color* rear_colors_end=rear_colors+end;
	for (rgb_color* led = rear_colors+start; (led != rear_colors_end); led++)
	{
		*led = (rgb_color
				)
				{ intensity, 0, 0 };
	}
}
