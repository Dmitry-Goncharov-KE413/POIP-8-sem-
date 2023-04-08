#include "ADC.h"
#include <cstdint> // ���������� ����������� ����� ������
#include "adc1registers.hpp" // ���������� ��� �������-��������� ��������������� (���)

void ADC::StartConversation()
{
  ADC1::CR2::SWSTART::On::Set(); // ������ ��� �� ��������������
  
}


int32_t ADC::GetResult()
{
  return static_cast<int32_t>(ADC1::DR::Get()); // static_cast 
  
  
}

/*bool ADC::IsConvertionComplete()
{
  //return ADC1::SR::EOC::ConvertionComplete::IsSet();
}*/


