/*
 * fireball.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

uint8_t lincrease[] = {1,1,1,1,2,2,2,2,2,2,3,3,3,3,4,4,4,5,5,6,6,7,7,8,9,9,10,11,12,13,15,16,17,19,21,23,25,27,29,32,35,38,41,45,49,54,59,64,70,76,83,90,98,107,117,128,139,152,165,180,197,214,234,255};

static void new_fireball(fireball_t* f, rgb_color* start, rgb_color* end)
{
	f->color = &rainbow[random(RAINBOW_MAX-1)];
//	f->speed = 0xFF>>random(FIREBALL_SPEED_DIVISOR_MIN, 8);
	f->speed = random(FIREBALL_SPEED_DIVISOR_MIN, FIREBALL_SPEED_DIVISOR_MAX);
	f->ticks = random(FIREBALL_MAX_WAIT);
	f->lut_increment = random(FIREBALL_MIN_LUT_INC, FIREBALL_MAX_LUT_INC);
	f->start = start;
	f->end = end;
	f->current = start;
	f->wrap = 1;
	f->lifetime = random(FIREBALL_MIN_LIFETIME, FIREBALL_MAX_LIFETIME);
	f->fade_in = 0;
	f->fade_out = 255;
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
		fb->lifetime--;
		if(fb->wrap)
		{
			uint8_t* value=(uint8_t*)star_table+64; //get the beginning of the star LUT
			rgb_color* pixel = fb->current+1; //start at the current pixel for the fb
			const uint8_t* stend = star_table;
			while((value)>stend && pixel!=fb->current)
			{
				//set our pixel to be the value from the LUT times the configured color
				apply_value(&tmp_color, fb->color, *value);
				if(fb->lifetime<64)
					apply_value(&tmp_color, &tmp_color, lincrease[fb->lifetime]);
				else if(fb->fade_in<64)
				{
					apply_value(&tmp_color, &tmp_color, lincrease[fb->fade_in]);
					fb->fade_in += !(frames & 0b00001111);
				}
				update_led(pixel, &tmp_color);
				//decrement the lifespan of the fireball
				//increment the pixel we are going to assign.
				pixel++;
				if(pixel>=(fb->end))
					pixel=fb->start;
				//increment our value based on the configured increment
				value-=fb->lut_increment;
			}
			if(fb->speed)
				fb->current+=!(frames % fb->speed);
			else
				fb->current++;
			if(fb->current >= (fb->end-1))
				fb->current = fb->start;
			if(0==fb->lifetime)
				new_fireball(fb, fb->start, fb->end);
		}
		else
		{
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
}
