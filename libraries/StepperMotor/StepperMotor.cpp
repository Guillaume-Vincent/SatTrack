#include "StepperMotor.h"


void pulseStep(unsigned int period) {
	digitalWrite(step_pin, HIGH);
	delayMicroseconds(period);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(period);	
}

void oneStepCW() {
	digitalWrite(dir_pin, LOW);
	pulseStep(1000);
}


void oneStepCCW() {
	digitalWrite(dir_pin, HIGH);
	pulseStep(1000);
}


void stepCW(unsigned int microstepNb) {
	for (int i=0; i<microstepNb; i++)
		oneStepCW();
}

void stepCCW(unsigned int microstepNb) {
	for (int i=0; i<microstepNb; i++)
		oneStepCCW();
}

void stepperMoveTo(float angle) {
	static float currentAngle = 0.0;

	unsigned int microstepNb;

	angle -= currentAngle;
	if (angle < -180.0) {
		angle += 360.0;
	}
	if (angle > 180.0) {
		angle -= 360.0;
	}

	microstepNb = 0.5 + 8 * abs(angle) / 1.8;

	if (angle > 0) {
		stepCW(microstepNb);
		currentAngle += microstepNb * 1.8 / 8.0;
	}
	else {
		stepCCW(microstepNb);
		currentAngle -= microstepNb * 1.8 / 8.0;
	}
}