#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "mqtt/IMqttPublisher.h"

class MqttPublisher : public IMqttPublisher {
  public:
    MqttPublisher();
    void connect() override;
    void loop() override;
    bool publish(const char *topic, const char *payload, bool retained) override;
    bool isConnected() override;
    bool isWifiConnected() override;
  private:
    WiFiClient esp_client_;
    PubSubClient client_;
    bool ensureWiFi();
    bool ensureMqtt();
    void startWiFi();
    uint32_t last_wifi_attempt_ms_;
    uint32_t last_mqtt_attempt_ms_;
};

#endif
