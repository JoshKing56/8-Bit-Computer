
#ifndef PROG_H
#define PROG_H

#define UPLOAD_PERIOD 100

void attach_upload_ISR();
void upload_program();
void get_new_program();

void clock_pulse(int last_write);
#endif
