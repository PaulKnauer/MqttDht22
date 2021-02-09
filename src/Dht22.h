#ifndef Dht22_h
#define Dht22_h

#include <SimpleDHT.h>

class Dht22 {
  public:
    Dht22();
    bool read();
    float getTemperature();
    float getHumidity();
  private:
    SimpleDHT22 *dht22;
    float temperature = 0;
    float humidity = 0;
};

#endif
