#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"
#include "Positions.h"


extern PositionsList * posList;
extern hw_timer_t * timer;
extern portMUX_TYPE timerMux;
extern volatile bool doGotoPosition;


void timerSetup();
void IRAM_ATTR onTimer();
void resetDoGotoPosition();


#endif
