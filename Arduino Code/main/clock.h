
#ifndef CLOCK_H
#define CLOCK_H

//timer library: https://code.google.com/archive/p/arduino-timerone/downloads
#include <TimerOne.h>

//https://github.com/PaulStoffregen/TimerThree/blob/master/TimerThree.h
#include <TimerThree.h>

#define system_clock_pin 13
#define display_clock_pin 12

#define SYSTEM_PORT PORTB
#define DISPLAY_PORT PORTB

#define SYSTEM_PORT_MASK_HIGH B10000000
#define SYSTEM_PORT_MASK_LOW B01111111
#define DISPLAY_PORT_MASK_HIGH B01000000
#define DISPLAY_PORT_MASK_LOW B10111111


void main_clock_ISR();
void display_clock_ISR();
void attach_timers();
void set_system_frequency();
byte frequency_method();        // check switch to choose measurement method
uint16_t read_ocl_register();   // read ocl register at analog_input_pins
int read_analog_input();        // frequency from potientiometer
int read_com_port();            // read frequecny from com port
int reading_to_freq();

#endif
