#include "InSender.h"
#include "usart2registers.hpp"    // Регистры USART для передачи данных
#include "Sender.h"

// конструктор
InSender::InSender(IDataSource& volt): _volt(volt)
{
  
}

void InSender::Execute() 
{
  for(;;)
  {
   float U =  _volt.GetData();
             
   Sender<USART2>::Send(U); // вывод символа в терминал
   Sleep(1000ms); 
  }

  
}
