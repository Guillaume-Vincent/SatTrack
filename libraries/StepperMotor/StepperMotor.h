#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"


const uint8_t step_pin = 11;
const uint8_t dir_pin = 13;

void stepperSetup();

void pulseStep(unsigned int period);

void oneStepCW();
void oneStepCCW();

void stepCW(unsigned int microstepNb);
void stepCCW(unsigned int microstepNb);

void stepperMoveTo(float angle);


#endif
