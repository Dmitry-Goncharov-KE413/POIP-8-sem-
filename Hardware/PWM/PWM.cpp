#include "PWM.h"
#include "tim3registers.hpp"         // ���������� ��� TIM3
#include <iostream> // ����������� ����������� ���������� �++


// �����������, ���������� ������ �� ������ � ����������
PWM::PWM(IDataSource& volt): _volt(volt) 
 {
   
 }
// �����, ������� ������������ ��R
float PWM::Calculate()
{
  float CCR = _volt.GetData() * TIM3::ARR::Get() / k;
  return CCR;   
} 