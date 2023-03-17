#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H
#include "IButtonObserver.h"


class IObservable
{
public:
  virtual void AddObserver (IButtonObserver& observer) = 0;
  
};

#endif