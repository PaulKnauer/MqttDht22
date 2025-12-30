#include "app/AppController.h"

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <stdint.h>
#include <stdio.h>

static inline uint32_t millis() {
  return 0;
}

static inline char *dtostrf(double val, signed char width, unsigned char prec, char *s) {
  (void)width;
  snprintf(s, 32, "%.*f", prec, val);
  return s;
}
#endif

#include "UserConfig.h"

AppController::AppController(ISensor &sensor, IMqttPublisher &publisher, StatusLed &status_led)
: sensor_(sensor),
  publisher_(publisher),
  status_led_(status_led),
  last_publish_ms_(0),
  last_heartbeat_ms_(0),
  consecutive_errors_(0) {}

void AppController::begin() {
  publisher_.connect();
}

void AppController::loop() {
  publisher_.loop();
  if (!publisher_.isWifiConnected()) {
    status_led_.setPattern(LedPattern::BlinkSlow);
  } else if (!publisher_.isConnected()) {
    status_led_.setPattern(LedPattern::BlinkFast);
  } else {
    status_led_.setPattern(LedPattern::SolidOn);
  }
  uint32_t now = millis();
  if (now - last_heartbeat_ms_ >= MQTT_HEARTBEAT_INTERVAL_MS) {
    last_heartbeat_ms_ = now;
    publisher_.publish(MQTT_HEARTBEAT_PUBLISH_TOPIC, MQTT_STATUS_ONLINE, true);
  }
  if (now - last_publish_ms_ < DELAY) {
    return;
  }
  last_publish_ms_ = now;
  SensorReading reading = sensor_.read();
  if (!reading.ok) {
    if (consecutive_errors_ < 255) {
      consecutive_errors_++;
    }
    if (consecutive_errors_ >= SENSOR_ERROR_THRESHOLD) {
      publisher_.publish(MQTT_STATUS_PUBLISH_TOPIC, MQTT_STATUS_OFFLINE, true);
      publisher_.publish(MQTT_ERROR_PUBLISH_TOPIC, "sensor_read_failed", true);
      status_led_.setPattern(LedPattern::PulseDouble);
    }
    return;
  }
  consecutive_errors_ = 0;

  char value[16];
  dtostrf(reading.temperature_c, 0, 1, value);
  publisher_.publish(MQTT_TEMPERATURE_PUBLISH_TOPIC, value, true);

  dtostrf(reading.humidity_percent, 0, 1, value);
  publisher_.publish(MQTT_HUMIDITY_PUBLISH_TOPIC, value, true);

#if MQTT_PUBLISH_JSON
  char payload[96];
  snprintf(payload, sizeof(payload),
           "{\"t\":%.1f,\"h\":%.1f,\"ms\":%lu,\"ok\":true}",
           reading.temperature_c,
           reading.humidity_percent,
           static_cast<unsigned long>(reading.timestamp_ms));
  publisher_.publish(MQTT_JSON_PUBLISH_TOPIC, payload, true);
#endif
}
