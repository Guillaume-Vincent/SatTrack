#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"


const float gear_ratio = 12.22 / 87.98;
const uint8_t step_pin = 11;
const uint8_t dir_pin = 13;


class StepperMotor {
public:
	StepperMotor(uint8_t step, uint8_t dir);

	void pulseStep(uint16_t period);
	void oneStepCW();
	void oneStepCCW();
	void stepCW(uint16_t microstepNb);
	void stepCCW(uint16_t microstepNb);
	void moveTo(float angle);

private:
	float currentAngle;
};


#endif
