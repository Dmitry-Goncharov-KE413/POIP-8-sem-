//
// Created by Sergey on 21.11.2019.
//

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP
#include "usart2registers.hpp"    // Регистры USART для передачи данных
#include "Sender.h"             // Файл передачи данных по USART

class InterruptHandler 
{
  public:
    static void DummyHandler() 
    { 
      for(;;) 
      {
        
      } 
    }

    static void USART2Handler() // Прервывание для USART2, вызыается когда опустошается регистр USART2::DR
    {
      if (USART2::SR::TXE::DataRegisterEmpty::IsSet() && USART2::CR1::TXEIE::InterruptWhenTXE::IsSet()) // Проверяем что регистр данных пуст USART2::SR::TXE и что разрешено прервание по передаче USART2::CR1::TXEIE
      {
        Sender<USART2>::SendOneSymvol(); // Функция передачи по 1 символу (по 1 байту), когда буфер опустошился, то передаём следующий символ
      }
    }
 
};



#endif //REGISTERS_INTERRUPTHANDLER_HPP
