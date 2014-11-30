/*
 * stars.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

const uint8_t star_table[] =
{ 4, 16, 64, 255, 255, 232, 211, 192, 175, 159, 145, 132, 120, 110, 100, 91, 83,
		75, 68, 62, 57, 52, 47, 43, 39, 35, 32, 29, 27, 24, 22, 20, 18, 17, 15,
		14, 13, 11, 10, 10, 9, 8, 7, 7, 6, 5, 5, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2,
		2, 2, 1, 1, 1, 1, 1 };
star_t stars[LED_COUNT];
star_t* stars_end = &stars[0] + LED_COUNT;
const uint8_t* star_table_end = &star_table[0] + 64;

inline uint8_t get_next()
{
	if (!rando)
		rando = (LED_COUNT - 1);
	return rando--;
}

void init_stars()
{
	for(uint8_t i=0; i<LED_COUNT; i++)
	{
		stars[i].lut_index = (uint8_t*) star_table_end;
		stars[i].ticks = random(STAR_MAX_TICKS);
		stars[i].pixel = &colors[i];
	}
//	for (star_t* star = stars; star != stars_end; star++)
//	{
//		star->lut_index = (uint8_t*) star_table_end;
//		star->ticks = random(STAR_MAX_TICKS);
//	}
}

void update_stars(uint8_t start, uint8_t end)
{
	star_t* stars_end = stars+end;
	star_t* star = stars+start;
	for (; star != stars_end; star++)
	{
		if (star->ticks)
		{
			star->ticks--;
		}
		else
		{
			star->lut_index++;
			if (star->lut_index < star_table_end)
			{
				rgb_color tmp = (rgb_color
						)
						{ *(star->lut_index), *(star->lut_index),
								*(star->lut_index) };
				//*(star->pixel) = (rgb_color){*(star->lut_index), *(star->lut_index), *(star->lut_index)};
				update_led(star->pixel, &tmp);
			}
			else
			{
				//*(star->pixel) = (rgb_color){0, 0, 0};
				//update_led(star->pixel, (rgb_color){*0,0,0});
//				star->pixel = colors + get_next();
				star->lut_index = star_table;
				star->ticks = random(STAR_MAX_TICKS);
			}
		}
	}
}
