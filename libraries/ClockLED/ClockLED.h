
#ifndef ClockLED_h
#define ClockLED_h

#include "Arduino.h"
#include "FastLED.h"



class ClockLED {
private:
	CRGB hourColor;
	CRGB minuteColor;
	CRGB secondColor;


public:
	void showClockLED(int hourLED, int minuteLED, int secondLED, CRGB cleds[] );
	void setClockColor(CRGB hColor, CRGB mColor, CRGB sColor);

};
#endif

