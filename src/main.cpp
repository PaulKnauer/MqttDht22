#include <Arduino.h>

#include "UserConfig.h"
#include "app/AppController.h"
#include "led/StatusLed.h"
#include "mqtt/MqttPublisher.h"
#include "sensors/Dht22Sensor.h"

MqttPublisher publisher;
Dht22Sensor sensor(DHT22_PIN);
StatusLed status_led(STATUS_LED_PIN, STATUS_LED_ACTIVE_LOW);
AppController app(sensor, publisher, status_led);

void setup() {
  status_led.begin();
  app.begin();
}

void loop() {
  status_led.loop(millis());
  app.loop();
}
