#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <stdint.h>

enum class LedPattern : uint8_t {
  Off,
  SolidOn,
  BlinkSlow,
  BlinkFast,
  PulseDouble
};

class StatusLed {
  public:
    explicit StatusLed(uint8_t pin, bool active_low);
    void begin();
    void setPattern(LedPattern pattern);
    void loop(uint32_t now_ms);
  private:
    void write(bool on);
    void updateBlink(uint32_t now_ms, uint32_t interval_ms);
    void updatePulseDouble(uint32_t now_ms);

    uint8_t pin_;
    bool active_low_;
    LedPattern pattern_;
    uint32_t last_toggle_ms_;
    bool state_on_;
};

#endif
