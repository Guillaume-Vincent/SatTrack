#include "StepperMotor.h"


StepperMotor::StepperMotor() {
	currentAngle = 0.0;

	pinMode(step_stp, OUTPUT);
	pinMode(dir_stp, OUTPUT);
	pinMode(en_stp, OUTPUT);
	disable();
}

void StepperMotor::init() {
	lcb.lcdPrintStepperInit();

	delay(1000);
	stepCW(8000);
	delay(1000);
	stepCCW(8000);
	delay(1000);
	
	lcb.lcdPrintStepperDone();
	delay(2000);
}

void StepperMotor::test() {
	uint16_t stepnb = 3600 * 8 / 2 / (gear_ratio * 1.8);
	lcb.lcdPrintStepperTest();
	delay(2000);
	stepCW(stepnb);
	stepCW(stepnb);
	delay(2000);
}

void StepperMotor::enable() {
	digitalWrite(en_stp, LOW);
}

void StepperMotor::disable() {
	digitalWrite(en_stp, HIGH);
}

void StepperMotor::pulseStep() {
	enable();
	digitalWrite(step_stp, HIGH);
	delayMicroseconds(pulse_delay);
	digitalWrite(step_stp, LOW);
	delayMicroseconds(pulse_delay);	
	disable();
}

void StepperMotor::oneStepCW() {
	digitalWrite(dir_stp, HIGH);
	pulseStep();
}

void StepperMotor::oneStepCCW() {
	digitalWrite(dir_stp, LOW);
	pulseStep();
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

float StepperMotor::getCurrentAngle() {
	return currentAngle;
}
