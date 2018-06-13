
#ifndef HM6264_H
#define HM6264_H

#include "Arduino.h"

#define OE_PIN_READ LOW
#define WE_PIN_WRITE LOW


class HM6264 {
  public:
    HM6264() {}
    HM6264(uint8_t address_pin_array[13], uint8_t data_pin_array[8], uint8_t OE, uint8_t WE, bool read_pins)
    {
      init(address_pin_array, data_pin_array, OE, WE, read_pins);
    }

    void write(int address, byte data);
    byte read(int address);
    void init(uint8_t address_pin_array[13], uint8_t data_pin_array[8], uint8_t OE, uint8_t WE, bool read_pins);


  private:

    byte OE_pin = 0;
    byte WE_pin = 0;
    byte data_pins [8] = {0};
    byte address_pins[13] = {0};

    bool read_using_same_pins = true;

    void set_upload_pins();
    void release_upload_pins();
    void enable_chip_write();
    void disable_chip_write();
    void disable_chip_read();
    void enable_chip_read();
    void set_data_pins();
    void set_address_pins();
    void release_address_pins();

    byte alt_read_func();

};



#endif HM6264_H
