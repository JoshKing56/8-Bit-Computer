
#include "clock.h"
#include "programmer.h"


void setup()
{
  
  attach_timers();
  attach_upload_ISR();

}

void loop()
{
  set_system_frequency();   //periodically set the system frequency
  delay(1000);
}




