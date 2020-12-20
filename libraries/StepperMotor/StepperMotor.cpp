#include "StepperMotor.h"


StepperMotor::StepperMotor() {
	currentAngle = 0.0;

	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	pinMode(en_pin, OUTPUT);
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

void StepperMotor::runTest() {
	lcb.lcdPrintStepperTest();

	for (float a=5.0; a<365.0; a+=5) {
		delay(1000);
		lcb.lcdPrintLine(0, a);
		moveTo(a);
	}
	delay(2000);
}

void StepperMotor::enable() {
	digitalWrite(en_pin, LOW);
}

void StepperMotor::disable() {
	digitalWrite(en_pin, HIGH);
}

void StepperMotor::pulseStep() {
	enable();
	digitalWrite(step_pin, HIGH);
	delayMicroseconds(pulse_delay);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(pulse_delay);	
	disable();
}

void StepperMotor::oneStepCW() {
	digitalWrite(dir_pin, HIGH);
	pulseStep();
}

void StepperMotor::oneStepCCW() {
	digitalWrite(dir_pin, LOW);
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
