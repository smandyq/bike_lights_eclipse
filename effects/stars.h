/*
 * stars.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef STARS_H_
#define STARS_H_
#include "../bike_lights.h"

#define LED_COUNT 150
#define STAR_MAX_TICKS 75

typedef struct
{
	rgb_color* pixel;
	const uint8_t* lut_index;
	uint8_t ticks;
} star_t;

//extern uint8_t frames;
extern uint8_t rando;
extern rgb_color colors[LED_COUNT];

void init_stars();
void update_stars();

#endif /* STARS_H_ */
