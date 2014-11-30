/* LedStripGradient: Example Arduino sketch that shows
 * how to control an Addressable RGB LED Strip from Pololu.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * you should see a pattern on the LED strip that fades from
 * green to pink and also moves along the strip.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PololuLedStrip.h"
#include "stars.h"
#include "bike_lights.h"

bool PololuLedStripBase::interruptFriendly = false;
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<9> ledStrip;

uint8_t frames;
uint8_t rando;
rgb_color colors[LED_COUNT];
rgb_color* colors_end;

rgb_color *led_end = &colors[0]+LED_COUNT;
rgb_color *led_start = &colors[0];
const uint8_t sin_table[] = {5,6,7,9,11,13,16,20,24,28,34,40,48,56,65,75,87,99,113,127,141,156,171,186,200,213,225,235,244,250,254,255,254,250,244,235,225,213,200,186,171,156,141,127,113,99,87,75,65,56,48,40,34,28,24,20,16,13,11,9,7,6,5,4};
const uint8_t cop_table[] = {255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
rgb_color rainbow[RAINBOW_MAX] = {
  {0xff, 0x00, 0x00},
  {0xff, 0x1f, 0x00},
  {0xff, 0xff, 0x00},
  {0x00, 0xff, 0x00},
  {0x00, 0x00, 0xff},
  {0x8f, 0x00, 0x8f}};

typedef struct
{
  rgb_color* start;
  rgb_color* end;
  rgb_color* color;
  uint8_t value;
  uint8_t speed;      //divisor for speed.  1, 3, 7 15, 31, 63, 127, or 255.  inversely proportional to speed.
  uint8_t lut_increment;     //increment for the lut.  higher number decreases length.
} fireball_t;

void update_led(rgb_color* pixel, rgb_color* color)
{
  memcpy(pixel, color, sizeof(rgb_color));
}

void update_cop()
{
  rgb_color copcolors[] = {{255, 0, 0}, {0, 0, 255}};
  static uint8_t on = 1;
  static rgb_color copcolor = copcolors[0];
  static uint8_t color_index;
  if(!(frames&63))
  {
    copcolor = copcolors[(color_index++) & 0x01];
  }
  if(cop_table[frames & 63])
  {
    for(rgb_color* pixel = colors; pixel!=colors_end; pixel++)
      *(pixel) = copcolor;
  }
  else
    for(rgb_color* pixel = colors; pixel!=colors_end; pixel++)
      *(pixel) = (rgb_color){0, 0, 0};
}

void update_breathe()
{
  static uint8_t intensity;
  static uint8_t breathe_tick;
  if(frames & 15)
    return;
  else
    breathe_tick = (breathe_tick +1) & 63;
  intensity = sin_table[breathe_tick];
  for(rgb_color* led = led_start; (led != led_end); led++)
  {
    *led = (rgb_color){ intensity, 0, 0 };
  }
}

void update_blank()
{
  memset(led_start, 0, sizeof(rgb_color)*LED_COUNT);
}

void setup()
{
	colors_end = &colors[0] + LED_COUNT;
	rando=0;
	init_stars();
  update_blank();
}

void loop()  //once per "frame" of data
{
  // Update the colors.
  //byte time = millis() >> 2;
  //update_breathe();
  update_blank();
  update_stars();
  //update_cop();

  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);
  frames++;
//  delay(50);
}
