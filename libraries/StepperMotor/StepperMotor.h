#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "Arduino.h"
#include "Constants.h"
#include "LiquidCrystalBoard.h"


extern LiquidCrystalBoard lcb;


class StepperMotor {
public:
	StepperMotor();

	void init();
	void runTest();
	void enable();
	void disable();
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
