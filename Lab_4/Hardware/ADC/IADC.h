#ifndef  IADC_H
#define  IADC_H

#include <cstdint> // библиотека подключения типов данных

class IADC
{
public:
    virtual void StartConversation() = 0;
    virtual int32_t GetResult() = 0;
    virtual bool IsConversionComplete() = 0;
};

#endif