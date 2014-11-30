/* LedStripGradient: Example Arduino sketch that shows
 * how to control an Addressable RGB LED Strip from Pololu.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * you should see a pattern on the LED strip that fades from
 * green to pink and also moves along the strip.
 */

#include "PololuLedStrip.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool PololuLedStripBase::interruptFriendly = false;
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<9> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 150
//#define STAR_COUNT 150
#define STAR_MAX_TICKS 75
rgb_color colors[LED_COUNT];
rgb_color* colors_end = &colors[0] + LED_COUNT;
uint8_t frames; //global frame counter

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

uint8_t ticks;
rgb_color *led_end = &colors[0]+LED_COUNT;
rgb_color *led_start = &colors[0];
const uint8_t sin_table[] = {5,6,7,9,11,13,16,20,24,28,34,40,48,56,65,75,87,99,113,127,141,156,171,186,200,213,225,235,244,250,254,255,254,250,244,235,225,213,200,186,171,156,141,127,113,99,87,75,65,56,48,40,34,28,24,20,16,13,11,9,7,6,5,4};
const uint8_t star_table[]  = {4,16,64,255,255,232,211,192,175,159,145,132,120,110,100,91,83,75,68,62,57,52,47,43,39,35,32,29,27,24,22,20,18,17,15,14,13,11,10,10,9,8,7,7,6,5,5,4,4,4,3,3,3,3,2,2,2,2,2,1,1,1,1,1};
const uint8_t cop_table[] = {255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
rgb_color rainbow[RAINBOW_MAX] = {
  {0xff, 0x00, 0x00},
  {0xff, 0x1f, 0x00},
  {0xff, 0xff, 0x00},
  {0x00, 0xff, 0x00},
  {0x00, 0x00, 0xff},
  {0x8f, 0x00, 0x8f}};
uint8_t rando = 0; //the current index of the random number we are on.

typedef struct
{
  rgb_color* pixel;
  const uint8_t*   lut_index;
  uint8_t    ticks;
} star_t;

typedef struct
{
  rgb_color* start;
  rgb_color* end;
  rgb_color* color;
  uint8_t value;
  uint8_t speed;      //divisor for speed.  1, 3, 7 15, 31, 63, 127, or 255.  inversely proportional to speed.
  uint8_t lut_increment;     //increment for the lut.  higher number decreases length.
} fireball_t;

star_t stars[LED_COUNT];
star_t* stars_end = &stars[0] + LED_COUNT;
const uint8_t* star_table_end = &star_table[0] + 64;

inline uint8_t get_rando()
{
  if(!rando)
    rando=(LED_COUNT-1);
  return rando--;
}

void update_led(rgb_color* pixel, rgb_color* color)
{
  memcpy(pixel, color, sizeof(rgb_color));
}

void update_stars()
{
  for(star_t* star = stars; star!=stars_end; star++)
  {
    if(star->ticks)
    {
      star->ticks--;
    }
    else
    {
      star->lut_index++;
      if(star->lut_index<star_table_end)
      {
        rgb_color tmp = (rgb_color){*(star->lut_index), *(star->lut_index), *(star->lut_index)};
        //*(star->pixel) = (rgb_color){*(star->lut_index), *(star->lut_index), *(star->lut_index)};
        update_led(star->pixel, &tmp);
      }
      else
      {
        //*(star->pixel) = (rgb_color){0, 0, 0};
        //update_led(star->pixel, (rgb_color){*0,0,0});
        star->pixel = colors + get_rando();
        star->lut_index = star_table;
        star->ticks = random(STAR_MAX_TICKS);
      }
    }
  }
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
  for(star_t* star = stars; star!=stars_end; star++)
  {
    star->lut_index=(uint8_t*)star_table_end;
    star->ticks = random(STAR_MAX_TICKS);
  }
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
