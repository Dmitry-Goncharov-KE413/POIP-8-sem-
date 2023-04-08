#include "OutSender.h"

OutSender::OutSender(OsWrapper::MailBox<int, 1>& outMailBox, IButton& button):
  buttonMailBox(outMailBox), _button(button)
{
  
}

void OutSender::Execute()
{
  int count = 0;
  for(;;)
  {
    if(_button.IsPressed())
    {
      buttonMailBox.Put(count & 3);
      count++;
    }
    Sleep(300ms);
  }
}




