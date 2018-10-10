

#include "Arduino.h"
#include "pins.h"
#include "programmer.h"

byte current_program[2 ^ ROM_NUM_ADDRESS_PINS][NUM_INSTRUCTION_ROM_CHIPS + NUM_CONTROL_ROM_CHIPS] = {0};

void attach_upload_ISR() {
  pinMode(UPLOAD_BUTTON, INPUT_PULLUP);
  attachInterrupt(UPLOAD_BUTTON, upload_program, FALLING);

#ifdef AUTO_UPLOAD
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, RESET_IDLE_STATE);
#endif
}

void upload_program() {
  noInterrupts();
  set_upload_pins();  //set as output for load
  for (int i = 0; i < 2 ^ ROM_NUM_ADDRESS_PINS; i++) //loop through address space
  {
    write_address(i);
    for (int j = 0; j < NUM_CONTROL_ROM_CHIPS+NUM_INSTRUCTION_ROM_CHIPS; j++) { //loop through instruction rom chips
      write_byte(i, j);
    }
  }
  release_upload_pins();  //set to input for saftey
  interrupts();

  software_reset();
}

void write_address(int address) {

  for (int k = ROM_ADDRESS_PIN_0; k < ROM_ADDRESS_PIN_0 + ROM_NUM_ADDRESS_PINS; k++) // write output pins
  {
    byte shift_by = k - ROM_ADDRESS_PIN_0;
    byte data_bit = ((address >> shift_by) & 1);
    
    digitalWrite(k, data_bit);
  }
}

void write_byte(int i, int j) {
  int last_write_time = micros();
  bool data_bit;
  for (int k = ROM_BYTE_PIN_0; k < ROM_BYTE_PIN_0 + ROM_NUM_BYTE_PINS; k++) // write output pins
  {
    byte shift_by = k - ROM_BYTE_PIN_0;
    data_bit = ((current_program[i][j] >> shift_by) & 1);
    digitalWrite(k, data_bit);
  }
  digitalWrite(ROM_CHIP_ENABLE_PIN_0 + j, ROM_ENABLE_WRITE);  //enable write pin
  clock_pulse(last_write_time);
  last_write_time = micros();
  digitalWrite(ROM_CHIP_ENABLE_PIN_0 + j, !ROM_ENABLE_WRITE);  //disable write pin
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

void set_upload_pins() {
  int k = 0;
  for (k = ROM_BYTE_PIN_0; k < ROM_BYTE_PIN_0 + ROM_NUM_BYTE_PINS; k++)
    pinMode(k, OUTPUT);
  for (k = ROM_ADDRESS_PIN_0; k < ROM_ADDRESS_PIN_0 + ROM_NUM_ADDRESS_PINS; k++)
    pinMode(k, OUTPUT);
  for (k = ROM_CHIP_ENABLE_PIN_0; k < ROM_CHIP_ENABLE_PIN_0 + ROM_NUM_ENABLE_PINS; k++)
    pinMode(k, OUTPUT);
}

void release_upload_pins() {
int k=0;
  for (k = ROM_BYTE_PIN_0; k < ROM_BYTE_PIN_0 + ROM_NUM_BYTE_PINS; k++)
    pinMode(k, INPUT);
  for (k = ROM_ADDRESS_PIN_0; k < ROM_ADDRESS_PIN_0 + ROM_NUM_ADDRESS_PINS; k++)
    pinMode(k, INPUT);
  for (k = ROM_CHIP_ENABLE_PIN_0; k < ROM_CHIP_ENABLE_PIN_0 + ROM_NUM_ENABLE_PINS; k++)
    pinMode(k, INPUT);
}


