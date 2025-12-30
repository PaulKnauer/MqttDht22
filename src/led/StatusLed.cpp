#include "led/StatusLed.h"

#include <Arduino.h>

StatusLed::StatusLed(uint8_t pin, bool active_low)
: pin_(pin),
  active_low_(active_low),
  pattern_(LedPattern::Off),
  last_toggle_ms_(0),
  state_on_(false) {}

void StatusLed::begin() {
  pinMode(pin_, OUTPUT);
  write(false);
}

void StatusLed::setPattern(LedPattern pattern) {
  if (pattern_ == pattern) {
    return;
  }
  pattern_ = pattern;
  last_toggle_ms_ = 0;
  state_on_ = false;
  write(false);
}

void StatusLed::loop(uint32_t now_ms) {
  switch (pattern_) {
    case LedPattern::Off:
      write(false);
      break;
    case LedPattern::SolidOn:
      write(true);
      break;
    case LedPattern::BlinkSlow:
      updateBlink(now_ms, 1000);
      break;
    case LedPattern::BlinkFast:
      updateBlink(now_ms, 250);
      break;
    case LedPattern::PulseDouble:
      updatePulseDouble(now_ms);
      break;
  }
}

void StatusLed::write(bool on) {
  bool level = active_low_ ? !on : on;
  digitalWrite(pin_, level ? HIGH : LOW);
}

void StatusLed::updateBlink(uint32_t now_ms, uint32_t interval_ms) {
  if (last_toggle_ms_ == 0 || (now_ms - last_toggle_ms_) >= interval_ms) {
    last_toggle_ms_ = now_ms;
    state_on_ = !state_on_;
    write(state_on_);
  }
}

void StatusLed::updatePulseDouble(uint32_t now_ms) {
  const uint32_t kPulseOnMs = 80;
  const uint32_t kPulseGapMs = 120;
  const uint32_t kPauseMs = 700;
  const uint32_t elapsed = (last_toggle_ms_ == 0) ? 0 : (now_ms - last_toggle_ms_);

  if (last_toggle_ms_ == 0) {
    last_toggle_ms_ = now_ms;
    state_on_ = true;
    write(true);
    return;
  }

  if (elapsed < kPulseOnMs) {
    write(true);
    return;
  }
  if (elapsed < kPulseOnMs + kPulseGapMs) {
    write(false);
    return;
  }
  if (elapsed < (2 * kPulseOnMs) + kPulseGapMs) {
    write(true);
    return;
  }
  if (elapsed < (2 * kPulseOnMs) + kPulseGapMs + kPauseMs) {
    write(false);
    return;
  }

  last_toggle_ms_ = now_ms;
  state_on_ = true;
  write(true);
}
