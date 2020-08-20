#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>
#include "Arduino.h"


const uint8_t servo_pin = 9;
const uint16_t minPosPeriod = 610;
const uint16_t maxPosPeriod = 2310;


uint16_t angleToPeriod(float angle);

class ServoMotor : public Servo {
public:
	ServoMotor();
	void init(uint8_t servo_pin);
	void moveTo(float angle);
};


#endif
