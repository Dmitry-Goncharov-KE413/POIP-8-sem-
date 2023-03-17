#include "Button.h"
#include "IButtonObserver.h"
#include "IObservable.h"


Button::Button(const IPinReadable& pin): _pin(pin)
{
  
}
// Кнопка нажата
bool Button::IsPressed() const 
{   
  if( !_pin.IsHigh() )  // Если кнопка не нажата 
  {
      while (!_pin.IsHigh()) // Если в како-то момент времени кнопка нажалась, то режим меняем
      {
         volatile int a = 1;
      }
      for(int i = 0; i <= _currentObserver; i++)
      {
        _observers[i] -> OnButtonPress();
      }
      return true;
  }
  return false;
}

void Button::AddObserver (IButtonObserver& observer)
{
  _currentObserver++;
  _observers[_currentObserver] = &observer;
}