
#include "pins.h"
#include "clock.h"
#include "programmer.h"

void setup() {
  
  attach_timers();
  attach_ocl_isr();
  attach_upload_ISR();    //upload on button push

}

void loop() {
  
  set_system_frequency(); // update the system frequency, if using ocl this is done with interrupts
  get_new_program();      // check for new received serial

}
