#include "Dht22.h"

Dht22::Dht22() {
  const int pinDHT22 = 2;
  dht22 = new SimpleDHT22(pinDHT22);
}

bool Dht22::read() {
  int err = SimpleDHTErrSuccess;
  if ((err = dht22->read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    return false;
  }
  return true;
}

float Dht22::getTemperature() {
  return (float) temperature;
}

float Dht22::getHumidity() {
  return (float) humidity;
}
