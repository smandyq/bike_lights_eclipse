/*
 * fireball.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "../bike_lights.h"

typedef struct
{
	rgb_color* start;
	rgb_color* end;
	rgb_color* color;
	uint8_t value;
	uint8_t speed; //divisor for speed.  1, 3, 7 15, 31, 63, 127, or 255.  inversely proportional to speed.
	uint8_t lut_increment; //increment for the lut.  higher number decreases length.
} fireball_t;

#endif /* FIREBALL_H_ */
