#ifndef SENDER_H
#define SENDER_H


#include <string>


template <typename TUSART>
class Sender
{
public:
  static void Send(std::string str)
  {
    i = 0; // переменная, отвечающая за длину строки
    localString = str;
    SendOneSymbol();
    TUSART::CR1::TE::Enable::Set();
    TUSART::CR1::TXEIE::InterruptWhenTXE::Set();
  }
  
  static void SendOneSymbol()
  {
    if(i > localString.size()) // если произошло достижение конца строки, ...
    {
      i = 0;
      TUSART::CR1::TE::Disable::Set(); // запрещаем передачу
      TUSART::CR1::TXEIE::InterruptInhibited::Set(); // запрещаем прерывание
    }
    else // иначе, если не достигли конца строки, ...
    {
      TUSART::DR::Write(localString[i]);
      i++;
    }
  }
  
private:
  static inline std::string localString; // строка отправки
  static inline int32_t i = 0U; // счетчик количества отправленных символов
};
#endif