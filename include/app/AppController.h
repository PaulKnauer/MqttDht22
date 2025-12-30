#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <stdint.h>

#include "sensors/ISensor.h"
#include "mqtt/IMqttPublisher.h"
#include "led/StatusLed.h"

class AppController {
  public:
    AppController(ISensor &sensor, IMqttPublisher &publisher, StatusLed &status_led);
    void begin();
    void loop();
  private:
    ISensor &sensor_;
    IMqttPublisher &publisher_;
    StatusLed &status_led_;
    uint32_t last_publish_ms_;
    uint32_t last_heartbeat_ms_;
    uint8_t consecutive_errors_;
};

#endif
