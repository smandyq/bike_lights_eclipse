#include "bike_lights.h"

bool PololuLedStripBase::interruptFriendly = false;
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<8> rear_strip;
PololuLedStrip<9> middle_strip;
PololuLedStrip<10> front_strip;

//{{0x03, 0x4f, 0x20}, {0xd4, 0x24, 0x26}};
rgb_color christmas[] = {{0x03, 0x8f, 0x20}, {0xff, 0x0, 0x0}};
rgb_color halogen = {255, 197, 143};

star_t front_stars[FRONT_LED_COUNT];
star_collection_t front_star_coll = {&halogen, 1, front_stars, FRONT_LED_COUNT, 50};

star_t mid_stars[MIDDLE_LED_COUNT];
star_collection_t mid_star_coll = {(rgb_color*)christmas, 2, mid_stars, MIDDLE_LED_COUNT, 5, 3};

star_t rear_stars[REAR_LED_COUNT];
star_collection_t rear_star_coll = {(rgb_color*)&rainbow[RED], 1, rear_stars, REAR_LED_COUNT, 10, 2};

fireball_t fireballs[FIREBALL_COUNT];

long timer;

void setup()
{
	int i=sizeof(int);
	int value = 0;
	while(i--)
	{
		value |=  EEPROM.read(i)<<i;
	}
	randomSeed(value);
	value++;
	i=sizeof(int);
	while(i--)
	{
		EEPROM.write(i, value>>i & 0xff);
	}
//	middle_colors_end = &middle_colors[0] + MIDDLE_LED_COUNT;
	rando = 0;
	init_stars(&front_star_coll, front_colors);
//	init_cop();
//	update_blank();
//	init_fireballs(fireballs, FIREBALL_COUNT, middle_colors, middle_colors+43);
	init_stars(&mid_star_coll, middle_colors);
	init_stars(&rear_star_coll, rear_colors);
}

uint32_t avg;
uint8_t count=0;

void loop()  //once per "frame" of data
{
	// Update the colors.
	//byte time = millis() >> 2;
	update_blank(middle_colors, MIDDLE_LED_COUNT);
	update_blank(front_colors, FRONT_LED_COUNT);
	update_blank(rear_colors, REAR_LED_COUNT);

//	update_breathe(0, REAR_LED_COUNT);
//	update_stars(138,150);
	update_stars(&front_star_coll, 0, 4);  //dead pixel situation
	update_stars(&front_star_coll, 5, FRONT_LED_COUNT);
	update_stars(&mid_star_coll, 0, MIDDLE_LED_COUNT);
	update_stars(&rear_star_coll, 0, REAR_LED_COUNT);
//	update_cop(125, 150);
//	timer = micros();
//	update_fireballs(fireballs, FIREBALL_COUNT);
//	timer = micros()-timer;
//	Serial.print(timer);
//	Serial.print("\r\n");
	// Write the colors to the LED strip.
	avg+=timer;

	for(rgb_color* c=middle_colors; c<middle_colors+MIDDLE_LED_COUNT; c++)
		apply_value(c, c, 255);
	middle_strip.write(middle_colors, MIDDLE_LED_COUNT);
	front_strip.write(front_colors, FRONT_LED_COUNT);
	rear_strip.write(rear_colors, REAR_LED_COUNT);

	frames++;
//	if(!frames)
//	{
//		Serial.print("average ");
//		Serial.print(count++);
//		Serial.print(": ");
//		Serial.print(avg/255);
//		Serial.print("\r\n");
//		avg=0;
//	}

//  delay(5);
}
