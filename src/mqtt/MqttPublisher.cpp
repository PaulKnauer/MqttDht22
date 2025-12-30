#include "mqtt/MqttPublisher.h"

#include <Arduino.h>

#include "UserConfig.h"

MqttPublisher::MqttPublisher()
    : client_(esp_client_), last_wifi_attempt_ms_(0), last_mqtt_attempt_ms_(0) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);
  startWiFi();
  client_.setServer(MQTT_SERVER, MQTT_SERVERPORT);
}

void MqttPublisher::connect() {
  ensureMqtt();
}

void MqttPublisher::loop() {
  if (ensureMqtt()) {
    client_.loop();
  }
}

bool MqttPublisher::publish(const char* topic, const char* payload, bool retained) {
  if (!client_.connected()) {
    return false;
  }
  return client_.publish(topic, payload, retained);
}

bool MqttPublisher::isConnected() {
  return client_.connected();
}

bool MqttPublisher::isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

bool MqttPublisher::ensureWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }
  uint32_t now = millis();
  if (now - last_wifi_attempt_ms_ < WIFI_RETRY_INTERVAL_MS) {
    return false;
  }
  last_wifi_attempt_ms_ = now;
  startWiFi();
  return false;
}

bool MqttPublisher::ensureMqtt() {
  if (!ensureWiFi()) {
    return false;
  }
  if (client_.connected()) {
    return true;
  }
  uint32_t now = millis();
  if (now - last_mqtt_attempt_ms_ < MQTT_RETRY_INTERVAL_MS) {
    return false;
  }
  last_mqtt_attempt_ms_ = now;
  if (client_.connect(MQTT_CLIENT_NAME, MQTT_USERNAME, MQTT_PASSWORD, MQTT_STATUS_PUBLISH_TOPIC, 1,
                      true, MQTT_STATUS_OFFLINE)) {
    client_.publish(MQTT_STATUS_PUBLISH_TOPIC, MQTT_STATUS_ONLINE, true);
    return true;
  }
  return false;
}

void MqttPublisher::startWiFi() {
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
}
