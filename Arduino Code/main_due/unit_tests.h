
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


};


#endif

