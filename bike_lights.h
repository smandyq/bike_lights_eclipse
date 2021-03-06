/*
 * bike_lights.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef BIKE_LIGHTS_H_
#define BIKE_LIGHTS_H_

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PololuLedStrip.h"
#include "effects/stars.h"
#include "effects/cop.h"
#include "effects/breathe.h"
#include "effects/fireball.h"
#include <EEPROM.h>

typedef enum
{
	RED, ORANGE, YELLOW, GREEN, BLUE, VIOLOET, CYAN, WHITE, RAINBOW_MAX
} rainbow_t;

const rgb_color rainbow[RAINBOW_MAX] =
{
{ 0xff, 0x00, 0x00 },
{ 0xff, 0x1f, 0x00 },
{ 0xff, 0xff, 0x00 },
{ 0x00, 0xff, 0x00 },
{ 0x00, 0x00, 0xff },
{ 0x8f, 0x00, 0x8f },
{ 0x00, 0xff, 0xff },
{ 0xff, 0xff, 0xff }};

//global frame counter for varying the framerate.
extern uint8_t frames;

//the current index of the random number we are on.
extern uint8_t rando;

//the actual array of colors to send to the led strip
extern rgb_color middle_colors[MIDDLE_LED_COUNT];
//pointer to the end of the color array
extern rgb_color* middle_colors_end;

//the actual array of colors to send to the led strip
extern rgb_color front_colors[FRONT_LED_COUNT];
//pointer to the end of the color array
extern rgb_color* front_colors_end;

//the actual array of colors to send to the led strip
extern rgb_color rear_colors[REAR_LED_COUNT];
//pointer to the end of the color array
extern rgb_color* rear_colors_end;

void update_led(rgb_color* pixel, rgb_color* color);
void update_blank(rgb_color* colors, uint8_t count);
void apply_value(rgb_color* dest, const rgb_color* color, const uint8_t value);

#endif /* BIKE_LIGHTS_H_ */
