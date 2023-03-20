#include "TreeMode.h"

TreeMode::TreeMode(const tArrayLeds& leds): IMode(leds)
{
  Clear();
}

void TreeMode:: Update()
{
  _leds[LedNumber]->Toggle();
  if(LedNumber == (size(_leds)-1))
  {
    LedNumber = 0;
  }
  else
  {
    LedNumber++;
  }
}