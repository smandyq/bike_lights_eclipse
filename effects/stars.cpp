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
		2, 2, 1, 1, 1, 1, 1, 0 };
//star_t* stars_end = &stars[0] + FRONT_LED_COUNT;
const uint8_t* star_table_end = &star_table[0] + 64;

inline uint8_t get_next()
{
	if (!rando)
		rando = (FRONT_LED_COUNT - 1);
	return rando--;
}

void init_stars(star_collection_t *star_coll, rgb_color *colors)
{
	for(uint8_t i=0; i<star_coll->stars_len; i++)
	{
		star_coll->stars[i].lut_index = (uint8_t*) star_table_end;
		star_coll->stars[i].ticks = random(255);
		star_coll->stars[i].pixel = &colors[i];
	}
//	for (star_t* star = stars; star != stars_end; star++)
//	{
//		star->lut_index = (uint8_t*) star_table_end;
//		star->ticks = random(STAR_MAX_TICKS);
//	}
}

void update_stars(star_collection_t *star_coll, uint8_t start, uint8_t end)
{
	star_t* stars_end = star_coll->stars+end;
	star_t* star = star_coll->stars+start;
	for (; star != stars_end; star++)
	{
		if (star->ticks)
		{
			star->ticks--;
		}
		else
		{
			if(!(star->ticks_per_frame--))
			{
				star->lut_index++;
				star->ticks_per_frame = star_coll->max_ticks_per_frame;
			}
			if (star->lut_index < star_table_end)
			{
				rgb_color tmp;
				apply_value(&tmp, star->current_color, *(star->lut_index));
				//*(star->pixel) = (rgb_color){*(star->lut_index), *(star->lut_index), *(star->lut_index)};
				update_led(star->pixel, &tmp);
			}
			else
			{
				//*(star->pixel) = (rgb_color){0, 0, 0};
				//update_led(star->pixel, (rgb_color){*0,0,0});
//				star->pixel = colors + get_next();
				if(star_coll->pallete_len > 1)
					star->current_color = &star_coll->pallete[random(star_coll->pallete_len)];
				else
					star->current_color = star_coll->pallete;
				star->lut_index = star_table;
				star->ticks = random(star_coll->max_ticks);
			}
		}
	}
}
