
#ifndef PIN_H //Защита от двойного подключения заголовочного файла
#define PIN_H //Защита от двойного подключения заголовочного файла

#include "gpiocregisters.hpp" 
#include <cinttypes> 

#include "ipin.h" // подключение интерфейса
#include "IPinReadable.h" // подключение интерфейса


template<typename TPort, int pinNum> // Отменяет привязку к типу порта, теперь можно сюда передать номер с любого порта (GPIOC, GPIOА)
class Pin: public IPin, public IPinReadable // Pin - класс наследник (наследование)
{ 
  public: 
  void Set() const // 
  {
    TPort::ODR::Set(1U << pinNum);
  }
  
  void Reset() const override
  {
    auto value = TPort::ODR::Get();
    value &=~(1U << pinNum);
    TPort::ODR::Write(value);
  } 
  void Toggle() const override //override - переопределение функции, которые есть в наследуемом классе интерфейсе
  {
    TPort::ODR::Toggle(1U << pinNum);
  } 
  
  bool IsHigh() const override
  {
    auto value = TPort::IDR::Get(); //получили значение входного регистра с состоянием ножек, 
    return ( (value & (1U << pinNum) ) == (1 << pinNum) ); // проверка на единичный бит 
  }
  
};



#endif //Защита от двойного подключения заголовочного файла