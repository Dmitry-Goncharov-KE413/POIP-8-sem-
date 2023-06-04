#include "ADC.h"
#include <cstdint>
#include "DMA.h"

// ���������� � ��������� ��������� code=0
ADC::ADC(): code(0)
{
 
}
 
// �����, ������� ���������� �������� ���
float ADC::GetData()
{
  return static_cast<float>(code);
} 

void ADC::Start()
{
   DMA::ConfigureADC(reinterpret_cast<std::uint32_t>(&code)); // ����� ����� code � ������������� � �����
}