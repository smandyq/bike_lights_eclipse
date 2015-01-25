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
	if(!(breathe_tick%5))
		intensity = 0;
	else
		intensity = sin_table[breathe_tick];
	rgb_color* colors_end=middle_colors+end;
	for (rgb_color* led = middle_colors+start; (led != colors_end); led++)
	{
		*led = (rgb_color
				)
				{ intensity, 0, 0 };
	}
}
