#include "MqttClient.h"

#include "Arduino.h"

MqttClient::MqttClient() {
  setUpWiFi();
  espClient = WiFiClient();
  client = PubSubClient(espClient);
  client.setServer(MQTT_SERVER, MQTT_SERVERPORT);
}

void MqttClient::connect() {
  while (!client.connected()) {
    if (!client.connect(MQTT_CLIENT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
      delay(5000);
    }
  }
}

void MqttClient::loop() {
  if (!client.connected()) {
    this->connect();
  }
  client.loop();
}

void MqttClient::publish(float value, const char *topic) {
  char *val = new char[4];
  dtostrf(value, 0, 1, val);
  client.publish(topic, val);
}

void MqttClient::setUpWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
