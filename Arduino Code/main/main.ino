//timer library: https://code.google.com/archive/p/arduino-timerone/downloads

#include "clock.h"
#include "programmer.h"


void setup()
{
  
  attach_timers();
}

void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
}

/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------



