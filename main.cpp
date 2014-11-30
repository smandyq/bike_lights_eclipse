#include "bike_lights.h"

bool PololuLedStripBase::interruptFriendly = false;
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<9> ledStrip;

void setup()
{
	colors_end = &colors[0] + LED_COUNT;
	rando = 0;
	init_stars();
	update_blank();
}

void loop()  //once per "frame" of data
{
	// Update the colors.
	//byte time = millis() >> 2;
	update_breathe();
	//update_blank();
	//update_stars();
	//update_cop();

	// Write the colors to the LED strip.
	ledStrip.write(colors, LED_COUNT);
	frames++;
//  delay(50);
}
