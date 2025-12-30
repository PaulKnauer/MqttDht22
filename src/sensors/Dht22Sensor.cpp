#include "sensors/Dht22Sensor.h"

Dht22Sensor::Dht22Sensor(uint8_t pin) : dht_(pin) {
  last_reading_.temperature_c = 0.0f;
  last_reading_.humidity_percent = 0.0f;
  last_reading_.timestamp_ms = 0;
  last_reading_.ok = false;
}

SensorReading Dht22Sensor::read() {
  float temperature = 0.0f;
  float humidity = 0.0f;
  int err = dht_.read2(&temperature, &humidity, NULL);
  last_reading_.timestamp_ms = millis();
  if (err == SimpleDHTErrSuccess) {
    last_reading_.temperature_c = temperature;
    last_reading_.humidity_percent = humidity;
    last_reading_.ok = true;
  } else {
    last_reading_.ok = false;
  }
  return last_reading_;
}
