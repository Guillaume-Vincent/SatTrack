#ifndef API_H
#define API_H

#include "Arduino.h"
#include "Constants.h"
#include "Positions.h"


extern PositionsList * posList;


void deserialize(String datastr);
void deserialize(char* datastr);


#endif
