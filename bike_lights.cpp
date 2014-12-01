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
	if(pixel->red < color->red)
		pixel->red = color->red;
	if(pixel->green < color->green)
		pixel->green = color->green;
	if(pixel->blue < color->blue)
		pixel->blue = color->blue;
//	memcpy(pixel, color, sizeof(rgb_color));
}

void update_blank()
{
	memset(colors, 0, sizeof(rgb_color) * LED_COUNT);
}

static uint8_t apply_weight(uint8_t b1, uint8_t b2)
{
	uint16_t tmp = b1*b2;
	return tmp>>8;
}
void apply_value(rgb_color* dest, const rgb_color* color, const uint8_t value)
{
	dest->red = apply_weight(color->red, value);
	dest->green = apply_weight(color->green, value);
	dest->blue = apply_weight(color->blue, value);
}
