#include "ADC.h"
#include <cstdint> // библиотека подключения типов данных
#include "adc1registers.hpp" // библиотека для аналого-цифрового преобразователя (АЦП)

void ADC::StartConversation()
{
  ADC1::CR2::SWSTART::On::Set(); // запуск АЦП на преобразование
  
}


int32_t ADC::GetResult()
{
  return static_cast<int32_t>(ADC1::DR::Get()); // static_cast 
  
  
}

/*bool ADC::IsConvertionComplete()
{
  //return ADC1::SR::EOC::ConvertionComplete::IsSet();
}*/


