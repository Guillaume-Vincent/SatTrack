#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>
#include "Arduino.h"
#include "LiquidCrystalBoard.h"
#include "Tools.h"


extern LiquidCrystalBoard lcb;

const uint8_t servo_pin = 9;
const uint16_t minPosPeriod = 610;
const uint16_t maxPosPeriod = 2310;


class ServoMotor : public Servo {
public:
	ServoMotor();
	void init();
	void moveTo(float angle);
};


#endif
