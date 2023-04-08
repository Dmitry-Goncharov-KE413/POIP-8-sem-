#include "Temperature.h"
#include <cstdint> // ���������� ����������� ����� ������
#include "adccommonregisters.hpp" // ���������� ��� �������-��������� ��������������� (���)

Temperature::Temperature(float vdda, float maxAdcValue, float v25, float avgSlope):
  _vdda(vdda), _maxAdcValue(maxAdcValue), _v25(v25), _avgSlope(_avgSlope)
  {
    
  }
  
  
  
float Temperature::Calculate(int32_t code)
{
  float temperatura = ( (code*_vdda/_maxAdcValue - _v25) / _avgSlope ) + temperature25; // ������� �������������� ���� � �����������
  return temperatura;
}