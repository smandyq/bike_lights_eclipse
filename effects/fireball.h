/*
 * fireball.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "../bike_lights.h"

#define FIREBALL_MAX_FREQ 50  //max amount of time to wait to fire a new fireball
#define FIREBALL_SPEED_DIVISOR_MIN 2 //maximum power of two to make the speed divisor
#define FIREBALL_SPEED_DIVISOR_MAX 7 //maximum power of two to make the speed divisor
#define FIREBALL_MAX_WAIT 63
#define FIREBALL_MAX_LUT_INC 8  //maximum amount of shortening of the tail of the fireball
#define FIREBALL_MIN_LUT_INC 5  //minimum amount of shortening of the tail of the fireball
#define FIREBALL_MAX_LIFETIME 1200
#define FIREBALL_MIN_LIFETIME 600


typedef struct
{
	rgb_color* start;        //the first pixel it will be allowed to hit
	rgb_color* current;      //the current "head" of the fireball
	rgb_color* end;          //the last pixel it will be allowed to hit
	const rgb_color* color;  //the color it should be
	uint8_t speed;           //divisor for speed.  1, 3, 7 15, 31, 63, 127, or 255.  inversely proportional to speed.
	uint8_t lut_increment;   //increment for the lut.  higher number decreases length.
	uint8_t ticks;           //time to wait to fire the fireball
	bool wrap:1;			 //when end is reached, go back to start
	bool fade:1;			 //fade out when its lifetime has ended.
	uint16_t lifetime;		 //counter to store how many update cycles it has survived.  at zero, it regenerates
	uint8_t fade_in;		 //fade in counter
	uint8_t fade_out;        //fade out counter
	uint8_t fade_inc;		 //fade in/out increment
} fireball_t;

void init_fireballs(fireball_t *fireballs, uint8_t count, rgb_color* start, rgb_color* end);
void update_fireballs(fireball_t* fireballs, uint8_t count);

#endif /* FIREBALL_H_ */
