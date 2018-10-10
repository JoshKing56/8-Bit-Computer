
#include "unit_tests.h"
#include "programmer.h"
#include "clock.h"
#include "Arduino.h"
#include "pins.h"

extern byte current_program[2 ^ ROM_NUM_ADDRESS_PINS][NUM_INSTRUCTION_ROM_CHIPS + NUM_CONTROL_ROM_CHIPS];

void Test::run_tests() {

  byte return_value = 0;
  Serial.println("\n\n");

  set_upload_pins();
  
  return_value = test_byte_write();
  if (return_value != 0) Serial.println("failed: test_byte_write");
  else Serial.println("passed: test_byte_write");

  return_value = test_address_write();
  if (return_value != 0) Serial.println("failed: test_address_write");
  else Serial.println("passed: test_address_write");
  
  Serial.println("Finished tests");

  release_upload_pins();
  #ifdef STOP_AFTER_TESTING
  while (1) {}
  #endif
}


byte Test::test_byte_write() {
  byte test_value = 170; // 10101010
  int expected_value[] = {1, 0, 1, 0, 1, 0, 1, 0};

  current_program[0][0] = test_value;
  write_byte(0, 0);
  for (int i = 0; i < ROM_NUM_BYTE_PINS; i++) {
    if (digitalRead(ROM_BYTE_PIN_0 + i) != expected_value[(ROM_NUM_BYTE_PINS - 1) - i])
      return 1;
  }
  return 0;
}

byte Test::test_address_write() {
  int test_value = 5461; // 1010101010101
  int expected_value[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};


  write_address(test_value);
  for (int i = 0; i < ROM_NUM_ADDRESS_PINS; i++) {
    if (digitalRead(ROM_ADDRESS_PIN_0 + i) != expected_value[(ROM_NUM_ADDRESS_PINS - 1) - i])
      return 1;
  }
  return 0;
}


