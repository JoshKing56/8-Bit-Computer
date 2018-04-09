

#include "Arduino.h"
#include "pins.h"
#include "clock.h"



void main_clock_ISR()
{
  static byte system_clock_flag = 0;
  // Toggle Pin
  //
  if (system_clock_flag == 1) { //If pin on.
    PORTB &= SYSTEM_PORT_MASK_LOW; //Turn pin off.
    system_clock_flag = 0;
  }
  else {
    PORTB |= SYSTEM_PORT_MASK_HIGH;
    system_clock_flag = 1;
  }
}

void display_clock_ISR()
{
  static byte display_clock_flag = 0;
  // Toggle Pin
  //
  if (display_clock_flag == 1) { //If pin on.
    PORTB &= DISPLAY_PORT_MASK_LOW; //Turn pin off.
    display_clock_flag = 0;
  }
  else {
    PORTB |= DISPLAY_PORT_MASK_HIGH;
    display_clock_flag = 1;
  }
}


void attach_timers() {

  pinMode(SYSTEM_CLOCK_PIN, OUTPUT);
  pinMode(DISPLAY_CLOCK_PIN, OUTPUT);

  Timer1.initialize(1000000/DEFAULT_SYSTEM_FREQ); // set a timer of length 10 microseconds (or 100,000Hz)
  Timer1.attachInterrupt( main_clock_ISR ); // attach the service routine here

  Timer3.initialize(1000000/DEFAULT_DISPLAY_FREQ);
  Timer3.attachInterrupt(display_clock_ISR);
}

void set_system_frequency() {
  int freq;
  switch (frequency_method()){
  case 1:   freq = reading_to_freq(read_ocl_register());  break;  
  case 2:   freq = reading_to_freq(read_analog_input());  break;
  case 3:   freq = reading_to_freq(read_com_port());      break;
  default:  freq = DEFAULT_SYSTEM_FREQ;
  }
  Timer1.setPeriod(1000000/freq);
}



byte frequency_method() {
  if (digitalRead(FREQ_METHOD_SWITCH1) && digitalRead(FREQ_METHOD_SWITCH2)) { //both high
    return (1);
  }
  else if ((digitalRead(FREQ_METHOD_SWITCH1) && !digitalRead(FREQ_METHOD_SWITCH2)) || (!digitalRead(FREQ_METHOD_SWITCH1) && digitalRead(FREQ_METHOD_SWITCH2))) { //different
    return (2);
  }

  else if (!digitalRead(FREQ_METHOD_SWITCH1) && !FREQ_METHOD_SWITCH2) { // both low
    return (3);
  }
  else return (4);  //error
}
uint16_t read_ocl_register(){}
uint16_t read_analog_input(){}
uint16_t read_com_port(){}
int reading_to_freq(uint16_t reading){}
