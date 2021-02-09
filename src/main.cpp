#include "UserConfig.h"
#include "MqttClient.h"
#include "Dht22.h"

MqttClient *client;
Dht22 *dht22;

void setup() {
  client = new MqttClient();
  client->connect();
  dht22 = new Dht22();
}

void loop() {
  client->loop();
  dht22->read();
  client->publish(dht22->getTemperature(), MQTT_TEMPERATURE_PUBLISH_TOPIC);
  client->publish(dht22->getHumidity(), MQTT_HUMIDITY_PUBLISH_TOPIC);
  delay(DELAY);
}
