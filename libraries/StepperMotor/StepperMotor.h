#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"
#include "Constants.h"
#include "LiquidCrystalBoard.h"


extern LiquidCrystalBoard lcb;


class StepperMotor {
public:
	StepperMotor(uint8_t step, uint8_t dir);

	void init();
	void pulseStep();
	void oneStepCW();
	void oneStepCCW();
	void stepCW(uint16_t microstepNb);
	void stepCCW(uint16_t microstepNb);
	void moveTo(float angle);

private:
	float currentAngle;
};


#endif
