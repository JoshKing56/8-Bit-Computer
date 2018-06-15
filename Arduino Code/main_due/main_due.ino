
#include "pins.h"
#include "clock.h"
#include "programmer.h"
#include "unit_tests.h"

#define STOP_AFTER_TESTING    //comment this to run program after testing finished

//Test test;

void setup() {
  Serial.begin(115200);
  attach_programmer();
  //test.run_tests();
  attach_timers();
  attach_ocl_isr();
  attach_upload_ISR();    //upload on button push

}

void loop() {
  
  set_system_frequency(); // update the system frequency, if using ocl this is done with interrupts
  get_new_program();      // check for new received serial

}
