
#ifndef PROG_H
#define PROG_H

#include "Arduino.h"

#define UPLOAD_PERIOD 100000   // clock to upload to rom
#define DELAY_PERIOD 1000    // when reading the program from pc, allow delays of this long between bytes

#define NOP_BYTE1 144       //0x900000
#define NOP_BYTE2 0
#define NOP_BYTE3 0

#define AUTO_UPLOAD    //define to upload automatically when new program arrived
#define RESET_IDLE_STATE HIGH

#define ROM_ENABLE_WRITE HIGH

#define NUM_INSTRUCTION_ROM_CHIPS 3
#define NUM_CONTROL_ROM_CHIPS 4


void attach_upload_ISR();
void upload_program();
byte get_new_program();
void write_address(int address);
void write_byte(int i, int j);
void clock_pulse(int last_write);
void software_reset();
void set_upload_pins();
void release_upload_pins();

#endif
