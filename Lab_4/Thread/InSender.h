#ifndef  INSENDER_H
#define  INSENDER_H

#include "Thread.hpp"
#include "MailBox.hpp"
#include "Iled.h"
#include "IMode.h"
#include <array>

using tArrayLeds = std::array<ILed*,4>;

class InSender: public OsWrapper::Thread<128>
{
public:
  void Execute() override;
  InSender(OsWrapper::MailBox<int, 1>& inMailBox, const tArrayLeds& leds);

  
private:
  OsWrapper::MailBox<int, 1>& buttonMailBox;
  const tArrayLeds& _leds;
};


#endif