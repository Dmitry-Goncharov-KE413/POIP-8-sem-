#ifndef  IMEASUREPARAMETER_H
#define  IMEASUREPARAMETER_H


class IMeasureParameter
{
public:
    virtual float Calculate(int32_t code) = 0;
};
#endif