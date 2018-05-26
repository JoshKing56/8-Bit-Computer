

#include "Arduino.h"
#include "pins.h"
#include "programmer.h"

byte current_program[2 ^ ROM_NUM_ADDRESS_PINS][3] = {0};

void attach_upload_ISR() {
  pinMode(UPLOAD_BUTTON, INPUT_PULLUP);
  attachInterrupt(UPLOAD_BUTTON, upload_program, FALLING);
}

void upload_program() {
  noInterrupts();
  //  digitalWrite(SYSTEM_CLOCK_PIN, HIGH);
  int last_write_time = micros();
  bool data_bit;
  for (int i = 0; i < 2 ^ ROM_NUM_ADDRESS_PINS; i++) {

    for (int k = 14; k <= 37; k++) // write output pins doing it the lazy way for now
    {
      data_bit = (current_program[i][((k - 14) / 8)] >> k);
      digitalWrite(k, data_bit);
    }

    clock_pulse(last_write_time);
    last_write_time = micros();
  }

  interrupts();

}


void get_new_program() {
  // check periodically for incomming program from serial port
  // if new program being written, unpack, save to array
  // once finished call upload_program function
}

void clock_pulse(int last_write) {

  while (micros() < last_write + (UPLOAD_PERIOD / 2)) {} //wait until time to set clock low
  digitalWrite(SYSTEM_CLOCK_PIN, LOW);
  while (micros() < last_write + (UPLOAD_PERIOD)) {} //wait until time to set clock high
  digitalWrite(SYSTEM_CLOCK_PIN, HIGH);

}


