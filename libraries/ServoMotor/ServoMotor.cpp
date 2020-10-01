#include "ServoMotor.h"


ServoMotor::ServoMotor()
: Servo() {}

void ServoMotor::init() {
	Servo::attach(servo_pin, minPosPeriod, maxPosPeriod);
	lcb.lcdPrintServoInit();
	
	moveTo(0.0);
	delay(1000);
	moveTo(-90.0);
	delay(1000);
	moveTo(90.0);
	delay(1000);
	moveTo(0.0);

	lcb.lcdPrintServoDone();
	delay(2000);
}

void ServoMotor::moveTo(float angle) {
	uint16_t period = angleToPeriod(angle, minPosPeriod, maxPosPeriod);
	Servo::writeMicroseconds(period);
}
