#ifndef INSENDER_H
#define INSENDER_H

#include "Thread.hpp"
#include "IMeasureParameter.h" 
#include "IDataSource.h"       // для интерфейса IDataSource для сбора данных 

class InSender: public OsWrapper::Thread<512> 
{

public:
  void Execute() override;
  InSender(IDataSource& volt); 
  
private:
     IDataSource& _volt;  
};

#endif
