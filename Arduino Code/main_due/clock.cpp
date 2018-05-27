

#include "Arduino.h"
#include "pins.h"
#include "clock.h"

void attach_timers() {
  pinMode (SYSTEM_CLOCK_PIN, OUTPUT) ;
  pinMode (DISPLAY_CLOCK_PIN, OUTPUT) ;

  Timer1.attachInterrupt(display_clock_isr);
  Timer1.start(DISPLAY_PERIOD);

  Timer2.attachInterrupt(system_clock_isr);
  Timer2.start(DEFAULT_PERIOD);
}

void attach_ocl_isr() { //point to the same interrupt for any pin change
  for (int i = 0; i < 14; i++) {
    attachInterrupt(OCL_REGISTER_PIN_0 + i, read_ocl_register, CHANGE);
  }
}

void set_system_frequency() {
  int freq;
  switch (frequency_method()) {
    case 1:
      break;  //ocl register, done through interrups
    case 2:
      freq = reading_to_freq(read_analog_input());
      Timer2.setPeriod(1000000 / freq);
      break;
    case 3:
      freq = reading_to_freq(read_com_port());
      Timer2.setPeriod(1000000 / freq);
      break;
    default:
      freq = DEFAULT_SYSTEM_FREQ;
      Timer2.setPeriod(1000000 / freq);
  }

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


void read_ocl_register() {
  // need to data coherancy, disable interrupts from output clocks temporarily, read pins and update timer period
  noInterrupts();
  uint32_t read_port_c = (PIOC->PIO_PDSR);
  uint32_t read_port_a = (PIOA->PIO_PDSR);
  uint8_t lower_bits = (read_port_c >> 5) & 0x000F ; // read C6-C9
  uint8_t middle_bits = (read_port_a >> 18) & 0x0003;
  uint8_t upper_bits = (read_port_c >> 11) & 0x00FF; // nb these are reverse order
  uint16_t reading = (upper_bits << 6) & (middle_bits << 4) & (lower_bits);

  Timer2.setFrequency(reading_to_freq(reading));
  interrupts();
}

uint16_t read_analog_input() {
  return (analogRead(ANALOG_POT_PIN) << 4); //map 10 bit reading to 14 bit
}



uint16_t read_com_port() {

}


int reading_to_freq(uint16_t reading) {

  if (reading < 256)     //slow reading
    return (map(reading, 1, 256, 0.2, 50));  //steps of 0.2ish Hz

  else    //fast reading
    return (map(reading, 257, 16384, 50, 250000));  // steps of 15.6ish hz
}


void system_clock_isr() {

  static byte system_clock_flag = 0;

  if (system_clock_flag == 1) {
    SYSTEM_CLOCK_PORT -> PIO_SODR = SYSTEM_CLOCK_PIN_MASK ;   // set pin
    system_clock_flag = 0;
  }
  else {
    SYSTEM_CLOCK_PORT -> PIO_CODR = SYSTEM_CLOCK_PIN_MASK ;  // clear pin
    system_clock_flag = 1;
  }
}


void display_clock_isr()
{
  static byte display_clock_flag = 0;

  if (display_clock_flag == 1) { //If pin on.
    DISPLAY_CLOCK_PORT -> PIO_SODR = DISPLAY_CLOCK_PIN_MASK; //Turn pin off.
    display_clock_flag = 0;
  }
  else {
    DISPLAY_CLOCK_PORT -> PIO_CODR = DISPLAY_CLOCK_PIN_MASK;
    display_clock_flag = 1;
  }
}


