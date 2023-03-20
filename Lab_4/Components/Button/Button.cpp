#include "Button.h"
#include "IButtonObserver.h"
#include "IObservable.h"


Button::Button(const IPinReadable& pin): _pin(pin)
{
  
}
// ������ ������
bool Button::IsPressed() const 
{   
  if( !_pin.IsHigh() )  // ���� ������ �� ������ 
  {
      while (!_pin.IsHigh()) // ���� � ����-�� ������ ������� ������ ��������, �� ����� ������
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