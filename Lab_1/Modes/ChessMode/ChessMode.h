//заголовочный файл для режима "Шахматы"
#ifndef CHESSMODE_H
#define CHESSMODE_H

#include "IMode.h"
#include  "Iled.h"


class ChessMode: public IMode
{
public: 
   ChessMode(const tArrayLeds& led) ;
   void Clear() override;
};

#endif