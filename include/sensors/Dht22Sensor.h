#ifndef DHT22_SENSOR_H
#define DHT22_SENSOR_H

#include <Arduino.h>
#include <SimpleDHT.h>

#include "sensors/ISensor.h"

class Dht22Sensor : public ISensor {
  public:
    explicit Dht22Sensor(uint8_t pin);
    SensorReading read() override;
  private:
    SimpleDHT22 dht_;
    SensorReading last_reading_;
};

#endif
