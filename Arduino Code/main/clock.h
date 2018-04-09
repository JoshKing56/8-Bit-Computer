
#ifndef CLOCK_H
#define CLOCK_H

#include <TimerOne.h>
#include <TimerThree.h>


void main_clock_ISR();
void display_clock_ISR();
void attach_timers();

#endif
