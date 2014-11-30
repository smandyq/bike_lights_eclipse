/*
 * fireball.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */
#include "../bike_lights.h"

fireball_t fireballs[FIREBALL_COUNT];

static void new_fireball(fireball_t* f)
{
	f->color = &rainbow[random(RAINBOW_MAX-1)];
	f->speed = random(FIREBALL_SPEED_DIVISOR_MAX);
	f->ticks = random(FIREBALL_MAX_WAIT);
	f->lut_increment = random(FIREBALL_MAX_LUT_INC);
}

void init_fireball()
{
	fireball_t* fireball_end = fireballs+FIREBALL_COUNT;
	for(fireball_t* f=fireballs; f<fireball_end; f++)
	{
		new_fireball(f);
	}
}

void update_fireball(uint8_t start, uint8_t end)
{

}
