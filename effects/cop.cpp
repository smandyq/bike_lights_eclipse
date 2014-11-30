/*
 * cop.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#include "../bike_lights.h"

uint8_t cop_tick;

void init_cop()
{
	cop_tick = 0;
}

void update_cop(uint8_t start, uint8_t end)
{
	static rgb_color copcolor = copcolors[0];
	static uint8_t color_index;
	static uint8_t wait;
	if(wait)
	{
		wait--;
		return;
	}
	cop_tick++;
	if (!(cop_tick & 63))
	{
		copcolor = copcolors[(color_index++) & 0x01];
		wait = 30;
	}
	else if (!(cop_tick & 9) || !(cop_tick & 8) )
	{
		rgb_color* colors_end = colors + end;
		for (rgb_color* pixel = colors + start; pixel != colors_end; pixel++)
			*(pixel) = copcolor;
	}
}

