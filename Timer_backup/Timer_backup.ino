
#include <FastLED.h>
#include <DS1307RTC.h>
#include <Wire.h>


#include <TimeAlarms.h>
#include <Time.h>

#define NUM_LEDS 60
#define DATA_PIN 10

CRGB leds[NUM_LEDS];


const unsigned short interrupt = 3;
const unsigned short mode1 = 4;
const unsigned short mode2 = 5;
const unsigned short mode3 = 6;
volatile unsigned int time_hour = 25, time_minute = 55, time_second = 3, time_day, time_month, time_year;
volatile unsigned long alteZeit = 0, alteZeit1 = 0, alteZeit2 = 0,  entprellZeit = 20;
time_t  t;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(mode1, INPUT);
  pinMode(mode2, INPUT);
  pinMode(mode3, INPUT);
  setTime(time_hour, time_minute , time_second, time_day, time_month, time_year);
  t = now();
  RTC.set(t);
  attachInterrupt(digitalPinToInterrupt(interrupt), mode, RISING);
}

void loop() {
  printTime();
  clockLED();
  delay(1000);


}

void printTime() {
  t = RTC.get();
  Serial.print(hour(t));
  Serial.print(".");
  Serial.print(minute(t));
  Serial.print(".");
  Serial.print(second(t));
  Serial.println();
}

void mode() {
  if ((millis() - alteZeit) > entprellZeit) {
    Serial.print("Interrupt ausgeloest");
    unsigned short temp = 1;
    while (temp == 1) {

      if (digitalRead(mode1) == true && (millis() - alteZeit1) > entprellZeit) {
           time_hour++;
           Serial.print("hour");
           Serial.println(time_hour);
           if (time_hour > 23) {
           time_hour = 0; 
           }
           
        alteZeit1 = millis();
       
      }
      if (digitalRead(mode2) == true && (millis() - alteZeit2) > entprellZeit) {
          time_minute++;
          if (time_minute > 59) {
          time_minute = 0;
          }
        
        alteZeit2 = millis();
      }
      if (digitalRead(mode3) == true && (millis() - alteZeit2) > entprellZeit) {
        temp++;
        Serial.println(temp);
        }
        alteZeit2 = millis();
      }
      
    setTime(time_hour, time_minute , time_second, time_day, time_month, time_year);
    alteZeit = millis();
  }
}

void clockLED() {

  for ( int i= 0; i<=59; i++) {
    leds[i] = CRGB::Black;
  }

  //leds[second(t)] = CRGB::Blue;

  for (int i = 0; i<=second(t); i++) {
    leds[i] = CRGB::Red; 
  }
  
  leds[hour(t)] = CRGB::Green;
  

  FastLED.show(); 
  
}

