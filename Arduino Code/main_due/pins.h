#ifndef PINS_H
#define PINS_H

#define UPLOAD_BUTTON 13
#define RESET_PIN 8
#define FREQ_METHOD_SWITCH1 9
#define FREQ_METHOD_SWITCH2 10

#define DISPLAY_CLOCK_PIN 12
#define SYSTEM_CLOCK_PIN 11

//port layout: https://forum.arduino.cc/index.php?topic=138519.0
#define ROM_BYTE_PIN_0 22   //22-29

#define ROM_ADDRESS_PIN_0 30  //30-42
#define ROM_NUM_ADDRESS_PINS 13 //number of pins used in address
#define ROM_NUM_BYTE_PINS 8
#define ROM_NUM_ENABLE_PINS 7
#define ROM_CHIP_ENABLE_PIN_0 44 //one hot coding for each rom chip



#define OCL_REGISTER_PIN_0 44 //port C6-9 A19-20 C12-19

#define ANALOG_POT_PIN A0



#endif
