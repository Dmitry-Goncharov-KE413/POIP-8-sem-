#include "PWM.h"
#include "tim3registers.hpp"         // библиотека для TIM3
#include <iostream> // подключение стандартной библиотеки С++


// Конструктор, содержащий ссылку на данные о напряжении
PWM::PWM(IDataSource& volt): _volt(volt) 
 {
   
 }
// Метод, который рассчитывает ССR
float PWM::Calculate()
{
  float CCR = _volt.GetData() * TIM3::ARR::Get() / k;
  return CCR;   
} 