#ifndef ISENSOR_H
#define ISENSOR_H

#include "sensors/SensorReading.h"

class ISensor {
  public:
    virtual ~ISensor() = default;
    virtual SensorReading read() = 0;
};

#endif
