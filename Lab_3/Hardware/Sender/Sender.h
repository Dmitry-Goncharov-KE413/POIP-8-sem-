#ifndef SENDER_H
#define SENDER_H


#include <string>


template <typename TUSART>
class Sender
{
public:
  static void Send(std::string str)
  {
    localString = str;
    TUSART::DR::Write(localString[i]);
    i++;
    TUSART::CR1::TE::Enable::Set();
    TUSART::CR1::TXEIE::InterruptWhenTXE::Set();
  }
  
  static void SendOneSymbol()
  {
    if(i > localString.size())
    {
      i = 0;
      TUSART::CR1::TE::Disable::Set();
      TUSART::CR1::TXEIE::InterruptInhibited::Set();
    }
    else
    {
      TUSART::DR::Write(localString[i]);
      i++;
    }
  }
  
private:
  static inline std::string localString;
  static inline int32_t i = 0U;
};
#endif