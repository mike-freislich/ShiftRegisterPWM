#include <Arduino.h>

#define DATA_PIN 4 // Shift Register - pin 14
#define LATCH_PIN 5
#define CLOCK_PIN 6
#define OUTPUT_ENABLE_PIN 3

#define ShiftRegisterPWM_IGNORE_PINS \
  {                                  \
    29, 30,31                        \
  }
#include "ShiftRegisterPWM.h"
#include "SimpleTimer.h"

#pragma region SETUP
void setup()
{
  //Serial.begin(57600);
  
}

#pragma endregion

void loop()
{
  ShiftRegisterPWM sr = ShiftRegisterPWM();
  sr.interrupt(ShiftRegisterPWM::UpdateFrequency::Medium);
  sr.setData(0xFFFFFFFF);

  int i = 0;
  sr.setPulseWidth(20);
  SimpleTimer t = SimpleTimer(200);
  SimpleTimer gate = SimpleTimer(50);
  SimpleTimer longTimer = SimpleTimer(3000);
  SimpleTimer enterTimer = SimpleTimer(5000);

  sr.set(31, 2);

  uint8_t brightness = 20;
  
  while (true)
  {
    sr.flash();

    if (gate.done())
    {           
      sr.toggle(26);
      sr.toggle(27);
      sr.toggle(29);
      sr.toggle(30);
      brightness = (brightness + 1) % 30;
    }

    if (enterTimer.done()) {
      sr.set(28, (sr.get(28)+1 % 3));
    }

    if (longTimer.done()) {
      sr.set(31, (sr.get(31)+1 % 2 + 1));
    }

    if (t.done())
    {      
      sr.toggle(i);
      sr.toggle(15 - i);
      i = (i + 1) % 8;      
    }
    
    sr.setPulseWidth(brightness);
  }
}
