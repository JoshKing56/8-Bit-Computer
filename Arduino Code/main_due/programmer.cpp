

#include "Arduino.h"
#include "pins.h"
#include "programmer.h"

byte current_program[2 ^ ROM_NUM_ADDRESS_PINS][3] = {0};

void attach_upload_ISR() {
  pinMode(UPLOAD_BUTTON, INPUT_PULLUP);
  attachInterrupt(UPLOAD_BUTTON, upload_program, FALLING);

#ifdef AUTO_UPLOAD
  pinMode(software_reset, OUTPUT);
  digitalWrite(RESET_PIN, RESET_IDLE_STATE);
#endif
}

void upload_program() {
  noInterrupts();

  int last_write_time = micros();
  bool data_bit;
  for (int i = 0; i < 2 ^ ROM_NUM_ADDRESS_PINS; i++) {

    for (int k = ROM_BYTE_1_PIN_0; k < ROM_BYTE_1_PIN_0 + 24; k++) // write output pins
    {
      data_bit = (current_program[i][((k - ROM_BYTE_1_PIN_0) / 8)] >> k);
      digitalWrite(k, data_bit);
    }

    clock_pulse(last_write_time);
    last_write_time = micros();
  }

  interrupts();

  software_reset();
}


byte get_new_program() {
  // check periodically for incomming program from serial port
  // if new program being written, unpack, save to array
  // once finished call upload_program function

  if (Serial.available() > 0) {
    uint8_t first_byte = Serial.read();   //program_size

    while (Serial.available() == 0) {} // wait for next byte to arrive
    uint8_t second_byte = Serial.read();  //second part of program size

    uint16_t program_size = (first_byte << 8) & second_byte;
    int last_byte_recieved = micros();
    int i = 0;

    for (i = 0; i < program_size; i++) { //read this number of bytes and write to array
      while (Serial.available() < 2) { //wait for bytes to arrive
        if (micros() < last_byte_recieved + DELAY_PERIOD) //if waiting long time, return error
          return (1); //error
      }
      current_program[i][1] = Serial.read();  // read instruction and put in array
      current_program[i][2] = Serial.read();
      current_program[i][3] = Serial.read();
      last_byte_recieved = micros();
    }

    for (i = program_size; i < 2 ^ ROM_NUM_ADDRESS_PINS; i++) {
      current_program[i][1] = NOP_BYTE1;  // fill remaining space with nop codes
      current_program[i][2] = NOP_BYTE2;
      current_program[i][3] = NOP_BYTE3;
    }

#ifdef AUTO_UPLOAD //configure to upload code immediately once pushed from computer
    upload_program();
#endif

  }
}

void clock_pulse(int last_write) {

  while (micros() < last_write + (UPLOAD_PERIOD / 2)) {} //wait until time to set clock low
  digitalWrite(SYSTEM_CLOCK_PIN, LOW);
  while (micros() < last_write + (UPLOAD_PERIOD)) {} //wait until time to set clock high
  digitalWrite(SYSTEM_CLOCK_PIN, HIGH);

}

void software_reset() {
  digitalWrite(RESET_PIN, !RESET_IDLE_STATE);   //cause reset
  delay(100);
  digitalWrite(RESET_PIN, RESET_IDLE_STATE);    //return to idle

}

