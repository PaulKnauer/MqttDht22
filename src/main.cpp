#include <Arduino.h>

#include "UserConfig.h"
#include "app/AppController.h"
#include "mqtt/MqttPublisher.h"
#include "sensors/Dht22Sensor.h"

MqttPublisher publisher;
Dht22Sensor sensor(DHT22_PIN);
AppController app(sensor, publisher);

void setup() {
  app.begin();
}

void loop() {
  app.loop();
}
