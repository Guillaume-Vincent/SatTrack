#ifndef TOOLS_H
#define TOOLS_H


#include "Arduino.h"


uint16_t angleToPeriod(float angle, uint16_t minPosPeriod, uint16_t maxPosPeriod);
int getLength(char* str);

#endif
