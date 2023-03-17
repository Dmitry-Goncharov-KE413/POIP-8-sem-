//заголовочный файл для режима "Горочка"
#ifndef SLIDEMODE_H
#define SLIDEMODE_H

#include "IMode.h" // подключение инерфейса IMode
#include  "ILED.h" // подключение интерфейса LED

class SlideMode: public IMode // наследование режима шахмат от интерфейса IMode
{
public: 
   SlideMode(const tArrayLeds& led) ; // передача светодиодов в режим шахмат
   void Update() override ; // переопределённая функция выключения светодиодов
   
private:
  uint32_t ledNumber = 0;  //  индекс светодиода
  bool revers = false;    // Флаг, отвечающий за прямой и обратной ход светодиодов
};

#endif