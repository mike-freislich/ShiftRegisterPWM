#include <Arduino.h>
//#include "ShiftRegisterPWM.h"

#pragma region SETUP

ShiftRegisterPWM *sr;
uint8_t brightness = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(4, OUTPUT); // data
  pinMode(5, OUTPUT); // latch
  pinMode(6, OUTPUT); // clock
  
  sr = new ShiftRegisterPWM(2, 255);
  sr->interrupt(ShiftRegisterPWM::UpdateFrequency::Fast);
  sr->set(0,(uint8_t)50);  
  //sr->set(2,(uint8_t)255);
}

#pragma endregion

void loop()
{

  

  //sr->set(15,(uint8_t)128);

  for (uint8_t i = 0; i < 8; i++)
  {
    //sr.set(i, true);
    //uint8_t val = (uint8_t)(((float)sin(millis() / 150.0 + i / 8.0 * 2.0 * PI) + 1) * 128);
    //sr->set(i, val);
  }
  //delay(10);
  
  brightness++;
}
