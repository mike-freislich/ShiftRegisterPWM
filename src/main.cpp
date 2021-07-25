#include <Arduino.h>

#define DATA_PIN 4 // Shift Register - pin 14
#define LATCH_PIN 5
#define CLOCK_PIN 6
#define OUTPUT_ENABLE_PIN 3

#define ShiftRegisterPWM_IGNORE_PINS {26,27,29,30}
#include "ShiftRegisterPWM.h"

#pragma region SETUP

void setup()
{
}

#pragma endregion

class Timer
{
private:
  uint32_t lastTime;
  uint32_t timeout;  
public:
  Timer(uint32_t timeout) { start(timeout); }
  uint32_t elapsed() { return millis() - lastTime; }
  void start(uint32_t timeout) { this->lastTime = millis(); this->timeout = timeout; }
  void cycle() {start(timeout);}
  bool finished() { return (millis() - lastTime >= timeout); }
};

void loop()
{
  ShiftRegisterPWM sr = ShiftRegisterPWM();
  sr.interrupt(ShiftRegisterPWM::UpdateFrequency::Medium);
  sr.setData(0xFFFFFFFF);   

  int i = 0;
  Timer t = Timer(500);  
  while (true)
  {    
    uint8_t val = constrain((((float)sin(millis() / 500.0 + 0 / 8.0 * 2.0 * PI) + 1) * 15),0, 255);
    sr.setPulseWidth(val);

    if (t.finished()) {         
      i = (i + 1) % 8;      
      t.cycle();
      sr.toggle(i);
      sr.toggle(8+i);
      sr.toggle(26);
      sr.toggle(27);
      sr.toggle(29);      
      sr.toggle(30);
    }
  }
}
