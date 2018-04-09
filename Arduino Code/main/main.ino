
#include "clock.h"
#include "programmer.h"


void setup()
{
  
  attach_timers();        // both clocks based on timer interrupts
  attach_upload_ISR();    //upload based on interrupt
  set_pins();
}

void loop()
{
  set_system_frequency();   //periodically set the system frequency
  delay(1000);
}


void set_pins(){ //setup all other pins 
  
  pinMode(FREQ_METHOD_SWITCH1, INPUT);
  pinMode(FREQ_METHOD_SWITCH2, INPUT);
  
  }

