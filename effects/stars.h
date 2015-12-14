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
	rgb_color* current_color;
	const uint8_t* lut_index;
	uint8_t ticks; //ticks between ending one star and starting a new one.
	uint8_t ticks_per_frame; //number of update cycles each frame should last
} star_t;

typedef struct
{
	rgb_color *pallete;
	size_t pallete_len;
	star_t* stars;
	size_t stars_len;
	uint8_t max_ticks; //maximum number of ticks between old star end, and new star start
	uint8_t max_ticks_per_frame;
} star_collection_t;

//extern uint8_t frames;
extern uint8_t rando;
extern rgb_color middle_colors[MIDDLE_LED_COUNT];
extern const uint8_t star_table[];
extern const uint8_t* star_table_end;

void init_stars(star_collection_t *star_coll, rgb_color *colors);
void update_stars(star_collection_t *star_coll, uint8_t start, uint8_t end);

#endif /* STARS_H_ */
