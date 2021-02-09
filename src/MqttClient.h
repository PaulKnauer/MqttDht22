#ifndef MqttClient_h
#define MqttClient_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "UserConfig.h"

class MqttClient {
  public:
    MqttClient();
    void connect();
    void loop();
    void publish(float value, const char *topic);
  private:
    WiFiClient espClient;
    PubSubClient client;
    void setUpWiFi();
};

#endif
