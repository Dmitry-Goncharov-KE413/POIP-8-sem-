//Интерфейс для различных режимов
#ifndef GARLAND_H
#define GARLAND_H
#include <iostream>

#include <array>
#include "IMode.h"
#include "IButtonObserver.h"


using tArrayModes = std::array<IMode*, 4>; // передача массива из режимов (4 режима)
class Garland : public IButtonObserver // Класс гирлянды, наследует интерфейс собитий кнопки
{
public: 
  Garland(const tArrayModes& modes): _modes(modes) // инициализация ссылки на массив режимов
  {
    
  }

  void UpdateCurrentMode() const // обновление состояния текущего режима
  {
     _modes[modeNumber]->Update();
  };

  void SwitchNextMode() // переключение режима на следующий
  {
    if (modeNumber == (_modes.size()-1)) 
    {
      modeNumber = 0;
    }
    else 
    { 
      modeNumber ++;
    }
    _modes[modeNumber]->Clear(); // сброс всех светодиодов
  };

  void OnButtonPress () override // собитие, при нажатии на кнопку
  {
    SwitchNextMode(); // переключиться на следующий режим
  }


private:
   uint32_t modeNumber = 0;    // счётчик режимов
   const tArrayModes& _modes;  // массив из режимов (4 штуки)

};
#endif