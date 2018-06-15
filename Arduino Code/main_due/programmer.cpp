

#include "Arduino.h"
#include "pins.h"
#include "programmer.h"
#include <Mux.h>
#include <HM6264.h>

byte current_program[2 ^ ROM_NUM_ADDRESS_PINS][NUM_INSTRUCTION_ROM_CHIPS + NUM_CONTROL_ROM_CHIPS] = {0};

HM6264 ROM[3];  //three rom chip objects in array

HM6264 Control[4];  //4 control chip objects



//read back function bridge variables
Mux Read_mux;
byte ram_chip_to_read;       // which chip do read from

void attach_programmer() {

  uint8_t data_array[ROM_NUM_BYTE_PINS];
  uint8_t addr_array[ROM_NUM_ADDRESS_PINS];

  uint8_t OE = ROM_CHIP_OUTPUT_ENABLE_PIN;
  uint8_t WE_array[ROM_NUM_ENABLE_PINS];

  for (int i = 0; i < ROM_NUM_BYTE_PINS; i++)
    data_array[i] = ROM_BYTE_PIN_0 + i;

  for (int i = 0; i < ROM_NUM_ADDRESS_PINS; i++)
    addr_array[i] = ROM_ADDRESS_PIN_0 + i;

  for (int i = 0; i < ROM_NUM_ENABLE_PINS; i++)
    WE_array[i] = ROM_CHIP_WRITE_ENABLE_PIN_0 + i;

  for (int i = 0; i < NUM_INSTRUCTION_ROM_CHIPS; i++)
    ROM[i].init(addr_array, data_array, OE, WE_array[i]);

  for (int i = 0; i < NUM_CONTROL_ROM_CHIPS; i++)
    Control[i].init(addr_array, data_array, OE, WE_array[i + NUM_INSTRUCTION_ROM_CHIPS]);

  byte mux_pin[4];
  for (int i = 0; i < NUM_MUX_PINS; i++)
    mux_pin[i] = COMMON_MUX_PIN_0 + i; // index pins

  disable_read_mux();   //set disable pins to low

  //attach read back hardware, use same select pins for all and toggle enable pin for specific bit
  Read_mux.setup(mux_pin[0], mux_pin[1], mux_pin[2], mux_pin[3], MUX_INPUT_PIN);

}

void disable_read_mux() {
  pinMode(ROM_1_2_MUX_ENABLE_PIN, OUTPUT);
  digitalWrite(ROM_1_2_MUX_ENABLE_PIN, READ_MUX_DISABLE_STATE);
  pinMode(ROM_3_MUX_ENABLE_PIN, OUTPUT);
  digitalWrite(ROM_3_MUX_ENABLE_PIN, READ_MUX_DISABLE_STATE);
  pinMode(CONTROL_1_MUX_ENABLE_PIN, OUTPUT);
  digitalWrite(CONTROL_1_MUX_ENABLE_PIN, READ_MUX_DISABLE_STATE);
  pinMode(CONTROL_2_MUX_ENABLE_PIN, OUTPUT);
  digitalWrite(CONTROL_2_MUX_ENABLE_PIN, READ_MUX_DISABLE_STATE);
}

byte read_back() {

  byte mux_enable_byte;
  byte start_value = 0;
  byte read_back_value=0;

  //configure 
  if (ram_chip_to_read == 0) {
    mux_enable_byte = ROM_1_2_MUX_ENABLE_PIN;
    start_value = 0;
  }
  else if (ram_chip_to_read == 1) {
    mux_enable_byte = ROM_1_2_MUX_ENABLE_PIN;
    start_value = 8;
  }
  else if (ram_chip_to_read == 2) {
    mux_enable_byte = ROM_3_MUX_ENABLE_PIN;
    start_value = 0;
  }
  else if (ram_chip_to_read == 3) {
    mux_enable_byte = CONTROL_1_MUX_ENABLE_PIN;
    start_value = 0;
  }
  else if (ram_chip_to_read == 4) {
    mux_enable_byte = CONTROL_1_MUX_ENABLE_PIN;
    start_value = 8;
  }
  else if (ram_chip_to_read == 5) {
    mux_enable_byte = CONTROL_2_MUX_ENABLE_PIN;
    start_value = 0;
  }
  else if (ram_chip_to_read == 6) {
    mux_enable_byte = CONTROL_2_MUX_ENABLE_PIN;
    start_value = 8;
  }
  
  //enable selected mux
  digitalWrite(mux_enable_byte, !READ_MUX_DISABLE_STATE);

  for (int i = 0; i < 8; i++) {
    read_back_value &= (((byte)Read_mux.read(start_value+i)) << i); //cast to byte, shift and sum 
  }
  //disable mux
  digitalWrite(mux_enable_byte, READ_MUX_DISABLE_STATE);
  return read_back_value;
}


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

  for (int i = 0; i < 2 ^ ROM_NUM_ADDRESS_PINS; i++) //loop through address space
  {
    for (int j = 0; j < NUM_INSTRUCTION_ROM_CHIPS; j++) {
      ROM[j].write(i, current_program[i][j]);
    }

    for (int j = NUM_INSTRUCTION_ROM_CHIPS; j < NUM_CONTROL_ROM_CHIPS + NUM_INSTRUCTION_ROM_CHIPS; j++) {
      Control[j].write(i, current_program[i][j]);
    }
  }
  interrupts();

  software_reset();
}


byte get_new_program() {
  // check periodically for incoming program from serial port
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

