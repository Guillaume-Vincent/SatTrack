#ifndef API_H
#define API_H
#define ARDUINOJSON_ENABLE_PROGMEM 1

#include "Arduino.h"
#include "Positions.h"


extern PositionsList * posList;

const uint8_t NB_OF_POSITIONS = 10;
const uint16_t JSON_MAX_SIZE = 13 + 14 * NB_OF_POSITIONS;

const char OBS_LAT[]  = "48.755";
const char OBS_LONG[] = "2.283";
const uint16_t OBS_ALT = 88;

void deserialize(char* datastr);

#endif
