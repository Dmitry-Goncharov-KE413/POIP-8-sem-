#ifndef  ADC_H
#define  ADC_H

#include "IADC.h"

class ADC: public IADC
{
public:
    void StartConversation() override; // метод будет преопределен
    int32_t GetResult() override; // метод будет преопределен
    //bool IsConvertionComplete() override;
};


#endif