#ifndef  TEMPERATURE_H
#define  TEMPERATURE_H

#include "IMeasureParameter.h"

class Temperature: public IMeasureParameter
{
public:
  Temperature(float vdda, float maxAdcValue, float v25, float avgSlope);
  float Calculate(int32_t code) override;
  
private:
  const float _vdda;
  const float _maxAdcValue;
  const float _v25;
  const float _avgSlope;
  static constexpr float temperature25 = 25;
};



#endif