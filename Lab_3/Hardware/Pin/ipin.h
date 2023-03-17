// Интерфейс класса Pin
#ifndef IPIN_H
#define IPIN_H

class IPin
{
public: 

  virtual void Reset() const=0; 
  virtual void Toggle() const=0 ; // виртуальный метод, у которого нет реализации
};

#endif