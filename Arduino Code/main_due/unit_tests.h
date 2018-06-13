
#ifndef TEST_H
#define TEST_H

#include "arduino.h"

class Test {
  public:
    Test() {}

    void run_tests();
  private:

    byte test_byte_write();
    byte test_address_write();
    byte write_byte_to_rom();
    byte read_data_from_rom(int read_address);

};


#endif

