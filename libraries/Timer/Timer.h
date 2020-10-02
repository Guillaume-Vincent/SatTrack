#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"
#include "API.h"
#include "Positions.h"
#include "Target.h"


extern PositionsList * posList;
extern volatile bool doGotoPosition;
extern volatile bool doUpdateRequest;
extern volatile float nextAzimuth;
extern volatile float nextElevation;


const uint8_t t2_load = 0;
const uint8_t t2_comp = 125;


void timerSetup();
ISR(TIMER2_COMPA_vect);


#endif
