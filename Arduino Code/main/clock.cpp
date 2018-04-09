
#include "Arduino.h"
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
  static byte display_clock_flag =0;
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


void attach_timers(){
  
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(system_clock_pin, OUTPUT);

  Timer1.initialize(100); // set a timer of length 10 microseconds (or 100,000Hz)
  Timer1.attachInterrupt( main_clock_ISR ); // attach the service routine here

  pinMode(display_clock_pin, OUTPUT);
  Timer3.initialize(30);
  Timer3.attachInterrupt(display_clock_ISR);
  }
