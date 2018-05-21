
#ifndef CLOCK_H
#define CLOCK_H

#include <DueTimer.h>

#define SYSTEM_CLOCK_PORT PIOB

//#define DISPLAY_PORT PORTB

#define SYSTEM_CLOCK_PIN_MASK (1<<27)   

#define DEFAULT_SYSTEM_FREQ 10000
#define DEFAULT_DISPLAY_FREQ 10000

void system_clock_isr();
void display_clock_ISR();
void attach_timers();
void set_system_frequency();
byte frequency_method();        // check switch to choose measurement method
uint16_t read_ocl_register();   // read ocl register at analog_input_pins
uint16_t read_analog_input();        // frequency from potientiometer
uint16_t read_com_port();            // read frequecny from com port
int reading_to_freq(uint16_t reading);

#endif
