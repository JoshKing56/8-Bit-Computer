
#include "pins.h"
#include "clock.h"
#include "programmer.h"

void setup() {
attach_timers();
attach_ocl_isr();
attach_upload_ISR();

}

void loop() {
   get_new_program();
}
