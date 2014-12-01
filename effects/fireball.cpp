/*
 * fireball.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

static void new_fireball(fireball_t* f, rgb_color* start, rgb_color* end)
{
	f->color = &rainbow[random(RAINBOW_MAX-1)];
//	f->speed = 0xFF>>random(FIREBALL_SPEED_DIVISOR_MIN, 8);
	f->speed = random(6);
	f->ticks = random(FIREBALL_MAX_WAIT);
	f->lut_increment = random(FIREBALL_MAX_LUT_INC);
	f->start = start;
	f->end = end;
	f->current = start;
}

void init_fireballs(fireball_t *fireballs, uint8_t count, rgb_color* start, rgb_color* end)
{
	fireball_t* fireball_end = fireballs+count;
	for(fireball_t* f=fireballs; f<fireball_end; f++)
	{
		new_fireball(f, start, end);
	}
}

void update_fireballs(fireball_t* fireballs, uint8_t count)
{
	fireball_t* end = fireballs+count;
	rgb_color tmp_color;
	for(fireball_t* fb=fireballs; fb<end; fb++)
	{
//		if(fb->ticks)
//			fb->ticks--;
		if(fb->start <= fb->current && fb->current < (fb->end+64))
		{
			uint8_t* value=(uint8_t*)star_table+64; //get the beginning of the star LUT
			rgb_color* pixel = fb->current-64; //start at the current pixel for the fb
			const uint8_t* stend = star_table-64;
			rgb_color* fbend = fb->end+64;

			while((value)>stend && pixel<fbend)
			{
				if(pixel >= fb->start && pixel<fb->end && value>star_table && value<star_table_end)
				{
				//set our pixel to be the value from the LUT times the configured color
				apply_value(&tmp_color, fb->color, *value);
				update_led(pixel, &tmp_color);
				}
				//increment the pixel we are going to assign.
				pixel++;
				//increment our value based on the configured increment
				value-=fb->lut_increment;
			}
			if(fb->speed)
				fb->current+=!(frames & fb->speed);
			else
				fb->current++;
		}
		else
			new_fireball(fb, fb->start, fb->end);
	}
}
