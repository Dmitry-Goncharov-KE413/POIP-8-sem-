#ifndef  IMEASUREPARAMETER
#define  IMEASUREPARAMETER

#include <cstdint> // библиотека подключения типов данных

class IMeasureParameter
{
public:
    virtual float Calculate(int32_t code) = 0;
};


#endif