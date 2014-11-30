/*
 * bike_lights.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef BIKE_LIGHTS_H_
#define BIKE_LIGHTS_H_

#include "PololuLedStrip.h"

#define LED_COUNT 150

typedef enum
{
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  VIOLOET,
  RAINBOW_MAX
} rainbow_t;


//global frame counter for varying the framerate.
extern uint8_t frames;

//the current index of the random number we are on.
extern uint8_t rando;

//the actual array of colors to send to the led strip
extern rgb_color colors[LED_COUNT];
//pointer to the end of the color array
extern rgb_color* colors_end;

void update_led(rgb_color* pixel, rgb_color* color);

#endif /* BIKE_LIGHTS_H_ */
