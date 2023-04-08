#ifndef  OUTSENDER_H
#define  OUTSENDER_H

#include "Thread.hpp"
#include "MailBox.hpp"
#include "IButton.h"

class OutSender: public OsWrapper::Thread<128>
{
public:
  void Execute();
  OutSender(OsWrapper::MailBox<int, 1>& outMailBox, IButton& button);
  
private:
  OsWrapper::MailBox<int, 1>& buttonMailBox;
  IButton& _button;
  
};


#endif