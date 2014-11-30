/*
 * bike_lights.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#include "bike_lights.h"

//stuff defined by extern in bike_lights.h
uint8_t frames;
uint8_t rando;
rgb_color colors[LED_COUNT];
rgb_color* colors_end;

void update_led(rgb_color* pixel, rgb_color* color)
{
	memcpy(pixel, color, sizeof(rgb_color));
}

void update_blank()
{
	memset(colors, 0, sizeof(rgb_color) * LED_COUNT);
}
