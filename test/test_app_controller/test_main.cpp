#include <unity.h>
#include <cstring>

#include "led/StatusLed.h"

#include "app/AppController.h"
#include "UserConfig.h"

class FakeSensor : public ISensor {
  public:
    SensorReading reading;
    FakeSensor() {
      reading.temperature_c = 23.4f;
      reading.humidity_percent = 56.7f;
      reading.timestamp_ms = 1234;
      reading.ok = true;
    }
    SensorReading read() override {
      return reading;
    }
};

class FakePublisher : public IMqttPublisher {
  public:
    static const uint8_t kMaxPublishes = 8;
    uint8_t publish_count = 0;
    char topics[kMaxPublishes][64];
    char payloads[kMaxPublishes][64];
    bool retained[kMaxPublishes];
    bool connected = true;
    bool wifi_connected = true;

    void connect() override {}
    void loop() override {}
    bool publish(const char *topic, const char *payload, bool retain) override {
      if (publish_count >= kMaxPublishes) {
        return false;
      }
      strncpy(topics[publish_count], topic, sizeof(topics[publish_count]) - 1);
      topics[publish_count][sizeof(topics[publish_count]) - 1] = '\0';
      strncpy(payloads[publish_count], payload, sizeof(payloads[publish_count]) - 1);
      payloads[publish_count][sizeof(payloads[publish_count]) - 1] = '\0';
      retained[publish_count] = retain;
      publish_count++;
      return true;
    }
    bool isConnected() const override {
      return connected;
    }
    bool isWifiConnected() const override {
      return wifi_connected;
    }

    bool hasTopic(const char *topic) const {
      for (uint8_t i = 0; i < publish_count; i++) {
        if (strcmp(topics[i], topic) == 0) {
          return true;
        }
      }
      return false;
    }
};

void test_publish_on_ok_reading() {
  FakeSensor sensor;
  FakePublisher publisher;
  StatusLed status_led(LED_BUILTIN, true);
  AppController app(sensor, publisher, status_led);

  app.begin();
  app.loop();

  TEST_ASSERT_EQUAL_UINT8(2, publisher.publish_count);
  TEST_ASSERT_EQUAL_STRING(MQTT_TEMPERATURE_PUBLISH_TOPIC, publisher.topics[0]);
  TEST_ASSERT_EQUAL_STRING(MQTT_HUMIDITY_PUBLISH_TOPIC, publisher.topics[1]);
}

void test_error_publishes_after_threshold() {
  FakeSensor sensor;
  FakePublisher publisher;
  StatusLed status_led(LED_BUILTIN, true);
  AppController app(sensor, publisher, status_led);

  sensor.reading.ok = false;
  app.begin();
  for (uint8_t i = 0; i < SENSOR_ERROR_THRESHOLD; i++) {
    app.loop();
  }

  TEST_ASSERT_TRUE(publisher.hasTopic(MQTT_STATUS_PUBLISH_TOPIC));
  TEST_ASSERT_TRUE(publisher.hasTopic(MQTT_ERROR_PUBLISH_TOPIC));
}

#ifdef UNIT_TEST
int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_publish_on_ok_reading);
  RUN_TEST(test_error_publishes_after_threshold);
  return UNITY_END();
}
#else
void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_publish_on_ok_reading);
  RUN_TEST(test_error_publishes_after_threshold);
  UNITY_END();
}

void loop() {}
#endif
