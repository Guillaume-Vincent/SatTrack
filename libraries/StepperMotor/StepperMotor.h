#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"


const unsigned int step_pin = 11;
const unsigned int dir_pin = 13;


void pulseStep(unsigned int period);

void oneStepCW();
void oneStepCCW();

void stepCW(unsigned int microstepNb);
void stepCCW(unsigned int microstepNb);

void stepperMoveTo(float angle);


#endif
