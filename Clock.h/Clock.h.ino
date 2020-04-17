#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock
{
  public:
    void printTime();
    void mode();
    void clockLED();
    
  private:
    volatile unsigned int time_hour, time_minute, time_second; 
};

#endif
