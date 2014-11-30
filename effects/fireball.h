/*
 * fireball.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "../bike_lights.h"

#define FIREBALL_COUNT 5
#define FIREBALL_MAX_FREQ 50  //max amount of time to wait to fire a new fireball
#define FIREBALL_SPEED_DIVISOR_MAX 8 //maximum power of two to make the speed divisor
#define FIREBALL_MAX_WAIT 64
#define FIREBALL_MAX_LUT_INC 8  //maximum amount of shortening of the tail of the fireball

typedef struct
{
	rgb_color* start;        //the first pixel it will be allowed to hit
	rgb_color* end;          //the last pixel it will be allowed to hit
	const rgb_color* color;  //the color it should be
	uint8_t speed;           //divisor for speed.  1, 3, 7 15, 31, 63, 127, or 255.  inversely proportional to speed.
	uint8_t lut_increment;   //increment for the lut.  higher number decreases length.
	uint8_t ticks;           //time to wait to fire the fireball
} fireball_t;

void init_fireball();
void update_fireball(uint8_t start, uint8_t end);

#endif /* FIREBALL_H_ */
