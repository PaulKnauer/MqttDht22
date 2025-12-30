#include <Arduino.h>
#include <unity.h>

void test_publish_on_ok_reading();
void test_error_publishes_after_threshold();

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_publish_on_ok_reading);
  RUN_TEST(test_error_publishes_after_threshold);
  UNITY_END();
}

void loop() {}
