#include <DueTimer.h>

#define pinnum 13
#define pinport PIOB
#define pinmask (1<<27)   // Arduino pin 2 is port B pin 25.

volatile byte flag = 0;

bool ledOn = false;
void myHandler() {
  if (flag == 1) {
    pinport -> PIO_SODR = pinmask ;   // set pin
    flag = 0;
  }
  else {
    pinport -> PIO_CODR = pinmask ;  // clear pin
    flag = 1;
  }
}

void setup() {
  pinMode (pinnum, OUTPUT) ;

  Timer3.attachInterrupt(myHandler);
  Timer3.start(1); // Calls every 50ms
}

void loop() {

}
