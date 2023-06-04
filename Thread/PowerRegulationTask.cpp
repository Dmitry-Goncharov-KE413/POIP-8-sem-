#include "PowerRegulationTask.h"
#include <iostream> // подключение стандартной библиотеки С++
#include <cstdint>                    // для int32_t
#include "tim3registers.hpp"         // библиотека для TIM3

// конструктор
PowerRegulationTask::PowerRegulationTask(IMeasureParameter& parameter): _parameter(parameter)
{
  
}
// Задача, которая записывает в таймер значение CCR
void PowerRegulationTask::Execute() 
{
  for(;;)
  {
   volatile auto  CCR = _parameter.Calculate();
   TIM3::CCR3::Write(static_cast<int32_t>(CCR));

   Sleep(100ms); 
  }
}