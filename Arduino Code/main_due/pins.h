#ifndef PINS_H
#define PINS_H

#define UPLOAD_BUTTON 2
#define RESET_PIN 3
#define FREQ_METHOD_SWITCH1 4
#define FREQ_METHOD_SWITCH2 5

#define DISPLAY_CLOCK_PIN 6
#define SYSTEM_CLOCK_PIN 7

#define OCL_REGISTER_PIN_0 8    //uses 14 individual pins to detect change and cause interrupt

#define ROM_BYTE_PIN_0 22   //22-29

#define ROM_ADDRESS_PIN_0 30  //30-42
#define ROM_NUM_ADDRESS_PINS 13 //number of pins used in address
#define ROM_NUM_BYTE_PINS 8
#define ROM_NUM_ENABLE_PINS 7
#define ROM_CHIP_WRITE_ENABLE_PIN_0 44 // one hot coding for each rom chip
#define ROM_CHIP_OUTPUT_ENABLE_PIN 52 // one disable to rule them all 


#define COMMON_MUX_PIN_0 54 //A0
#define ROM_1_2_MUX_ENALBE_PIN 58   //for rom chips 1 and 2
#define ROM_3_MUX_ENABLE_PIN 59     //for rom chip 3
#define CONTROL_1_MUX_ENABLE_PIN 60 //for control chips 1,2
#define CONTROL_2_MUX_ENABLE_PIN 61 //for control chips 3,4
#define MUX_INPUT PIN 53
#define ANALOG_POT_PIN 65   //A11
#define NUM_MUX_PINS 4



#endif
