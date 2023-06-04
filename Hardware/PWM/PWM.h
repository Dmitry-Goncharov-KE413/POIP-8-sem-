#ifndef PWM_H
#define PWM_H

#include "IMeasureParameter.h" // ��� ���������� IMeasureParameter ��� ������ Calculate()
#include "IDataSource.h"       // ��� ���������� IDataSource ��� ����� ������ 

// �����, ������� ���������� ���-������
class PWM: public IMeasureParameter
{
public: 
  explicit PWM(IDataSource& volt);  
  float Calculate() override;
  
private: 
  IDataSource& _volt;
  // ����������� ���������
  static constexpr float k = 3.3f;  // ������������ �������� �������� ������� TIM3
  static constexpr float b = 0.0f;  // � �������
}; 

#endif