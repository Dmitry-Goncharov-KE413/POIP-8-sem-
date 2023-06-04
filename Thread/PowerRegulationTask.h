#ifndef POWERREGULATIONTASK_H
#define POWERREGULATIONTASK_H

#include "Thread.hpp"
#include "IMeasureParameter.h" 
// Задача, которая подаёт на вывод частоту с определённым коэффициентом заполнения
class PowerRegulationTask: public OsWrapper::Thread<512> 
{
public:
  PowerRegulationTask(IMeasureParameter& parameter); 
  void Execute() override; 
  
private: // приватный атрибут, который хранит ссылку на интерфейс (его инициализация находится в PowerRegulationTask.cpp)
   IMeasureParameter& _parameter;   
};

#endif
