//заголовочный файл для режима "Ёлочка"
#ifndef TREEMODE_H
#define TREEMODE_H

#include "IMode.h"
#include "ipin.h"

class TreeMode: public IMode
{
public:
   TreeMode(const tArrayLeds& led);
   void Update() override;
   
public:
  uint32_t LedNumber = 0;
};
#endif