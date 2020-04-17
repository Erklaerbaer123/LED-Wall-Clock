
#include <FastLED.h>
#include <DS1307RTC.h>
#include <Wire.h>


#include <TimeAlarms.h>
#include <Time.h>

#define NUM_LEDS 60
#define DATA_PIN 10

CRGB leds[NUM_LEDS];


const unsigned short mode0 = 3;
const unsigned short mode1 = 5;
const unsigned short mode2 = 7;
const unsigned short mode3 = 9;
volatile unsigned int time_hour = 12, time_minute = 59, time_second = 55, time_day, time_month, time_year;
volatile unsigned long alteZeit = 0, alteZeit1 = 0, alteZeit2 = 0, alteZeit3 = 0, alteZeit4 = 0, entprellZeit = 1000, warteZeit = 1000;
bool setLight = true;


time_t  t;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(mode1, INPUT);
  pinMode(mode2, INPUT);
  pinMode(mode3, INPUT);
  pinMode(mode0, INPUT);
  setTime(time_hour, time_minute , time_second, time_day, time_month, time_year);
  t = now();
  RTC.set(t);
  hourFormat12(); 
}

void loop() {

  if( (millis() - alteZeit3) > warteZeit){
    printTime();
    clockLED();
    alteZeit3 = millis();
  }
  if (digitalRead(mode0) == true) {
    mode();
  }

  if(digitalRead(mode1) == true && (millis() - alteZeit4) > warteZeit ) {

    Serial.println("LIight On/off");
    if(setLight == true) {
      setLight = false;  
    }
    else {
      setLight = true;
    }
    clockLED();
    alteZeit4 = millis();
  }
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

    blinken();
    Serial.println("Interrupt ausgeloest");
    unsigned short temp = 1;
    while (temp == 1) {

      if (digitalRead(mode1) == true && (millis() - alteZeit1) > entprellZeit) {
           time_hour++;
           Serial.print("hour");
           Serial.println(time_hour);
           if (time_hour > 11) {
           time_hour = 0; 
           }
        setTime(time_hour, time_minute , time_second, time_day, time_month, time_year);
        clockLED();   
        alteZeit1 = millis();
       
      }
      if (digitalRead(mode2) == true && (millis() - alteZeit2) > entprellZeit) {
          time_minute++;
          if (time_minute > 59) {
          time_minute = 0;
          
          }
        
        setTime(time_hour, time_minute , time_second, time_day, time_month, time_year);
        clockLED();
        alteZeit2 = millis();
      }
      if (digitalRead(mode0) == true && (millis() - alteZeit3) > entprellZeit) {
        temp++;
        Serial.println(temp);
        alteZeit3 = millis();
        }
        
      }
    t = now();
    RTC.set(t);  
    Serial.println("Mode Ende");  
    blinken();  
    alteZeit = millis();
  }
}

void clockLED() {

  for ( int i= 0; i<=59; i++) {
    leds[i] = CRGB::Black;
  }

  for (int i = 0; i<=minute(t); i++) {
    leds[i] = CRGB::Red; 
  }

  if (hour(t) == 12 || hour(t) == 0) {
    leds[hour(t)*5] = CRGB::Green;
    leds[59] = CRGB::Green;
    leds[hour(t)*5+1] = CRGB::Green;
    
  }
  
  else {
    leds[hour(t)*5] = CRGB::Green;
    leds[hour(t)*5-1] = CRGB::Green;
    leds[hour(t)*5+1] = CRGB::Green; 
  }


  if(setLight == false) {
     for ( int i= 0; i<=59; i++) {
    leds[i] = CRGB::Black;
    }
  }

  FastLED.show(); 
  
}

void blinken() {

    for ( int i= 0; i<=59; i++) {
       leds[i] = CRGB::Red;
    }

    FastLED.show();
    delay(500);
    clockLED();
  
}


