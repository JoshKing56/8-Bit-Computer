
#ifndef CLOCK_H
#define CLOCK_H

#include <DueTimer.h>

#define SYSTEM_CLOCK_PORT PIOD
#define DISPLAY_CLOCK_PORT PIOD

#define SYSTEM_CLOCK_PIN_MASK (1<<7)
#define DISPLAY_CLOCK_PIN_MASK (1<<8)   

#define DEFAULT_SYSTEM_FREQ 100000 //starting clock speed in hz
#define DEFAULT_PERIOD ((int)(1/DEFAULT_SYSTEM_FREQ)*1000000)
#define TARGET_REFRESH_RATE 50 // in Hz
#define SCREEN_SIZE 16 //in bytes
#define DISPLAY_PERIOD ((int)((1/TARGET_REFRESH_RATE)*1000000)/SCREEN_SIZE)




void system_clock_isr();
void display_clock_isr();
void attach_timers();
void attach_ocl_isr();
void set_system_frequency();
byte frequency_method();        // check switch to choose measurement method
void read_ocl_register();   // read ocl register at analog_input_pins
uint16_t read_analog_input();        // frequency from potientiometer
uint16_t read_com_port();            // read frequecny from com port
int reading_to_freq(uint16_t reading);

#endif
