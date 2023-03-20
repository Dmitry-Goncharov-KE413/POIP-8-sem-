//Интерфейс класса кнопки
#ifndef IBUTTON_H
#define IBUTTON_H


class IButton
{
public: 
  virtual bool IsPressed() const=0;
};

#endif