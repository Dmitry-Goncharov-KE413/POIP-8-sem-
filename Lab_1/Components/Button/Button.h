#ifndef  BUTTON_H
#define  BUTTON_H

#include "IButton.h"
#include "IPinReadable.h"
#include "IButtonObserver.h"
#include "IObservable.h"
#include <array>

class Button : public IButton, public IObservable
{
public: 
  Button(const IPinReadable& pin); 
  
  bool IsPressed() const override; 
  void AddObserver(IButtonObserver& observer) override;
  
private:
    const IPinReadable& _pin;
    std::array<IButtonObserver*, 4> _observers;
    int32_t _currentObserver = -1;
};

#endif