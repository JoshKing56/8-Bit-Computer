

#include "Arduino.h"
#include "pins.h"
#include "programmer.h"



void attach_upload_ISR(){
    pinMode(UPLOAD_BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(UPLOAD_BUTTON), upload_program, FALLING);
}

void upload_program(){

}

