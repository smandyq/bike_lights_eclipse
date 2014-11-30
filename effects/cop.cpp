/*
 * cop.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#include "../bike_lights.h"

void update_cop(uint8_t start, uint8_t end)
{
	rgb_color copcolors[] =
	{
	{ 255, 0, 0 },
	{ 0, 0, 255 } };
	static rgb_color copcolor = copcolors[0];
	static uint8_t color_index;
	if (!(frames & 63))
	{
		copcolor = copcolors[(color_index++) & 0x01];
	}
	if (cop_table[frames & 63]) //if were about to overflow
	{
		for (rgb_color* pixel = colors; pixel != colors_end; pixel++)
			*(pixel) = copcolor;
	}
}

