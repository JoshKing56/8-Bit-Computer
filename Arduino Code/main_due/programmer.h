
#ifndef PROG_H
#define PROG_H

#define UPLOAD_PERIOD 100   // clock to upload to rom
#define DELAY_PERIOD 100    // when reading the program from pc, allow delays of this long between bytes

#define NOP_BYTE1 144       //0x900000
#define NOP_BYTE2 0
#define NOP_BYTE3 0

// #define AUTO_UPLOAD    //define to upload automatically when new program arrived
#define RESET_IDLE_STATE HIGH


void attach_upload_ISR();
void upload_program();
byte get_new_program();

void clock_pulse(int last_write);
void software_reset();
#endif
