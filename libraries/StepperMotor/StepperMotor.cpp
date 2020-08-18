#include "StepperMotor.h"


StepperMotor::StepperMotor(uint8_t step, uint8_t dir) {
	currentAngle = 0.0;

	pinMode(step, OUTPUT);
	pinMode(dir, OUTPUT);
}

void StepperMotor::pulseStep(uint16_t period) {
	digitalWrite(step_pin, HIGH);
	delayMicroseconds(period);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(period);	
}

void StepperMotor::oneStepCW() {
	digitalWrite(dir_pin, LOW);
	pulseStep(250);
}

void StepperMotor::oneStepCCW() {
	digitalWrite(dir_pin, HIGH);
	pulseStep(250);
}

void StepperMotor::stepCW(uint16_t microstepNb) {
	for (uint16_t i=0; i<microstepNb; i++)
		oneStepCW();
}

void StepperMotor::stepCCW(uint16_t microstepNb) {
	for (uint16_t i=0; i<microstepNb; i++)
		oneStepCCW();
}

void StepperMotor::moveTo(float angle) {
	unsigned int microstepNb;

	angle -= currentAngle;
	if (angle < -180.0) {
		angle += 360.0;
	}
	if (angle > 180.0) {
		angle -= 360.0;
	}

	microstepNb = 0.5 + 8 * abs(angle) / (1.8 * gear_ratio);
	if (angle > 0) {
		stepCW(microstepNb);
		currentAngle += microstepNb * gear_ratio * 1.8 / 8.0;
		if (currentAngle > 180.0)
		    currentAngle -= 360.0;
	}
	else {
		stepCCW(microstepNb);
		currentAngle -= microstepNb * gear_ratio * 1.8 / 8.0;
		if (currentAngle < -180.0)
		    currentAngle += 360.0;
	}
}
