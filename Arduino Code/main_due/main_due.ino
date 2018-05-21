
#include "pins.h"
#include "clock.h"
#include "programmer.h"

void setup() {
  pinMode (SYSTEM_CLOCK_PIN, OUTPUT) ;

  Timer3.attachInterrupt(system_clock_isr);
  Timer3.start(1); // Calls every 50ms
}

void loop() {

}
