#include "bike_lights.h"

bool PololuLedStripBase::interruptFriendly = false;
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<9> ledStrip;

fireball_t fireballs[FIREBALL_COUNT];

long timer;

void setup()
{
	colors_end = &colors[0] + LED_COUNT;
	rando = 0;
	init_stars();
	init_cop();
	update_blank();
	init_fireballs(fireballs, FIREBALL_COUNT, colors, colors_end);
}

uint32_t avg;
uint8_t count=0;

void loop()  //once per "frame" of data
{
	// Update the colors.
	//byte time = millis() >> 2;
	update_blank();

	update_breathe(25,50);
	//update_stars(0,50);
	update_stars(0, 25);
	update_cop(125, 150);
	timer = micros();
	update_fireballs(fireballs, FIREBALL_COUNT);
	timer = micros()-timer;
//	Serial.print(timer);
//	Serial.print("\r\n");
	// Write the colors to the LED strip.
	avg+=timer;

	ledStrip.write(colors, LED_COUNT);

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

//  delay(50);
}
