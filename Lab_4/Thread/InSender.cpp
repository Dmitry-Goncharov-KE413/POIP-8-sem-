#include "InSender.h"


InSender::InSender(OsWrapper::MailBox<int, 1>& inMailBox, const tArrayLeds& leds):
  buttonMailBox(inMailBox), _leds(leds)
{
  
}

void InSender::Execute()
{
  for(;;)
  {
    int i = -1;
    if(buttonMailBox.Get(i, 1000ms))
    {
      if((i >= 0) && (i <= std::size(_leds)))
      {
        _leds[i] -> Toggle();
      }
    }
  }
  Sleep();
}

