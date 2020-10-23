#ifndef API_H
#define API_H

#include "Arduino.h"
#include "Positions.h"


extern PositionsList * posList;

const uint8_t NB_OF_POSITIONS = 60;
const uint16_t JSON_MAX_SIZE = 13 + 14 * NB_OF_POSITIONS + 1;


void deserialize(String datastr);
void deserialize(char* datastr);

#endif
