// Интерфейс класса Считывание кнопки
#ifndef IPINREADABLE_H
#define IPINREADABLE_H

class IPinReadable
{
public: 

  virtual bool IsHigh() const=0;
  
};

#endif