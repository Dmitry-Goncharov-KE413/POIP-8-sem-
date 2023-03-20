//заголовочный файл для режима "Моргать всеми"
#ifndef ALLMODE_H
#define ALLMODE_H

#include "IMode.h"
#include "iled.h"



class AllMode: public IMode
{
public: 
   AllMode(const tArrayLeds& leds) ;
};

#endif