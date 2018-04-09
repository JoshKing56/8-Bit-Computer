
#include "pins.h"
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


void set_pins() { //setup all other pins

  pinMode(FREQ_METHOD_SWITCH1, INPUT);
  pinMode(FREQ_METHOD_SWITCH2, INPUT);

  pinMode(ANALOG_POT_PIN, INPUT);
  int i;
  
  for (i = 0; i < 8; i++)
    pinMode(ROM_BYTE_1_PIN_0 + i, OUTPUT);

  for (i = 0; i < 8; i++)
    pinMode(ROM_BYTE_2_PIN_0 + i, OUTPUT);

  for (i = 0; i < 8; i++)
    pinMode(ROM_BYTE_3_PIN_0 + i, OUTPUT);

  for (i = 0; i < 14; i++)
    pinMode(OCL_REGISTER_PIN_0 + i, INPUT);

    
}

