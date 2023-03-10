//Интерфейс класса Led
#ifndef ILED_H
#define ILED_H


class ILed
{
public: 
  virtual void SwithOff() const=0; 
  virtual void Toggle() const=0; 
};

#endif