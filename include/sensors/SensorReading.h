#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <stdint.h>

struct SensorReading {
  float temperature_c;
  float humidity_percent;
  uint32_t timestamp_ms;
  bool ok;
};

#endif
