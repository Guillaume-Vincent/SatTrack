#include "ServoMotor.h"


uint16_t angleToPeriod(float angle) {
    return 0.5 + (angle + 90.0) * (maxPosPeriod - minPosPeriod) / 180.0 + minPosPeriod;
}


ServoMotor::ServoMotor()
: Servo() {}

void ServoMotor::init(uint8_t servo_pin) {
	Servo::attach(servo_pin, minPosPeriod, maxPosPeriod);
	moveTo(0.0);
}

void ServoMotor::moveTo(float angle) {
	uint16_t period = angleToPeriod(angle);
	Servo::writeMicroseconds(period);
}
