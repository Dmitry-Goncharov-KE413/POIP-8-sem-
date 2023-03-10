#include "Led.h"


Led::Led(const IPin& pin): _pin(pin)
{
  
}
// потушить светодиод
void Led::SwithOff() const
{
  _pin.Reset();
}

// переключить светодиод
void Led::Toggle() const
{
  _pin.Toggle();
}