/*
 * stars.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef STARS_H_
#define STARS_H_
#include "../bike_lights.h"

#define STAR_MAX_TICKS 50

typedef struct
{
	rgb_color* pixel;
	const uint8_t* lut_index;
	uint8_t ticks;
} star_t;

//extern uint8_t frames;
extern uint8_t rando;
extern rgb_color middle_colors[MIDDLE_LED_COUNT];
extern const uint8_t star_table[];
extern const uint8_t* star_table_end;

void init_stars();
void update_stars(uint8_t start, uint8_t end);

#endif /* STARS_H_ */
