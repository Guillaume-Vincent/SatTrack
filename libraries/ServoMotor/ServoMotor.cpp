#include "ServoMotor.h"


ServoMotor::ServoMotor()
: Servo() {}

void ServoMotor::init() {
	Servo::attach(servo_pin, Servo::CHANNEL_NOT_ATTACHED, -90.0, 90.0, minPosPeriod, maxPosPeriod);
	lcb.lcdPrintServoInit();
	
	moveTo(0.0);
	delay(2000);
	moveTo(-90.0);
	delay(2000);
	moveTo(90.0);
	delay(2000);
	moveTo(0.0);

	lcb.lcdPrintServoDone();
	delay(2000);
}

void ServoMotor::moveTo(float angle) {
	Servo::write(angle);
}
