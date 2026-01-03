#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <stdint.h>

#include "sensors/ISensor.h"
#include "mqtt/IMqttPublisher.h"

class AppController {
public:
  AppController(ISensor& sensor, IMqttPublisher& publisher);
  void begin();
  void loop();

private:
  ISensor& sensor_;
  IMqttPublisher& publisher_;
  uint32_t last_publish_ms_;
  uint32_t last_heartbeat_ms_;
  uint8_t consecutive_errors_;
};

#endif
