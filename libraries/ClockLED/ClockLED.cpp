#include "ClockLED.h"
#include "Arduino.h"
#include "FastLED.h"

void ClockLED::showClockLED(int hourLED, int minuteLED, int secondLED, CRGB cleds[]) {

	for (int i = 0; i <= 59; i++) {
		leds[i] = CRGB::Black;
	}

	cleds[hourLED] = hourColor;
	cleds[minuteLED] = minuteColor;
	cleds[secondLED] = secondColor;

	
}

void ClockLED::setClockColor(CRGB hColor, CRGB mColor, CRGB sColor) {
	hourColor = hColor;
	minuteColor = mColor;
	secondColor = sColor;
}