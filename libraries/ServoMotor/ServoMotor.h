#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include "Arduino.h"
#include "LiquidCrystalBoard.h"
#include "Tools.h"
#include "Servo.h"


extern LiquidCrystalBoard lcb;

const uint8_t servo_pin = 13;
const uint16_t minPosPeriod = 560; // 600;
const uint16_t maxPosPeriod = 2285; //2300;


class ServoMotor : public Servo {
public:
	ServoMotor();
	void init();
	void moveTo(float angle);
};


#endif
