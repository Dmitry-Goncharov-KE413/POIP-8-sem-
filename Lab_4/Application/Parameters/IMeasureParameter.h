#ifndef  IMEASUREPARAMETER
#define  IMEASUREPARAMETER

#include <cstdint> // ���������� ����������� ����� ������

class IMeasureParameter
{
public:
    virtual float Calculate(int32_t code) = 0;
};


#endif