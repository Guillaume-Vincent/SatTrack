#ifndef API_H
#define API_H

#define ARDUINOJSON_ENABLE_PROGMEM 1

#include <avr/pgmspace.h>
#include <ArduinoJson.h>
#include "Arduino.h"
#include "positions.h"


const char input1[] PROGMEM = "{\"A\":[271.8,271.81,271.82,271.83,271.84,271.85,271.87,271.88,271.89,271.9,271.91,271.92,271.93,271.94,271.96],\"E\":[-71.26,-71.23,-71.2,-71.17,-71.14,-71.1,-71.07,-71.04,-71.01,-70.98,-70.94,-70.91,-70.88,-70.85,-70.82],\"I\":25544,\"N\":\"SPACE STATION\",\"S\":15,\"T\":0.6271708011627197}";
const char input2[] PROGMEM = "{\"A\":[314.09,314.07,314.05,314.04,314.02,314,313.98,313.96,313.94,313.92,313.91,313.89,313.87,313.85,313.83],\"E\":[-41.72,-41.75,-41.78,-41.82,-41.85,-41.88,-41.91,-41.94,-41.97,-42.01,-42.04,-42.07,-42.1,-42.13,-42.17],\"I\":33591,\"N\":\"NOAA 19\",\"S\":15,\"T\":0.6422076225280762}";
const char input3[] PROGMEM = "{\"A\":[300.9,300.85,300.8,300.75,300.7,300.65,300.61,300.56,300.51,300.46,300.41,300.36,300.31,300.26,300.21],\"E\":[-15.11,-15.07,-15.04,-15.01,-14.97,-14.94,-14.9,-14.87,-14.83,-14.8,-14.77,-14.73,-14.7,-14.66,-14.63],\"I\":45787,\"N\":\"STARLINK-1517\",\"S\":15,\"T\":0.670717716217041}";

const float OBS_LAT = 48.755;
const float OBS_LONG = 2.283;
const uint16_t OBS_ALT = 88;

const String API_BASE_URL = "192.168.43.1:5000/satpos/";
const String OBS_DATA = String("/") + String(OBS_LAT, 3) + "/" + String(OBS_LONG, 3) + "/" + OBS_ALT + "/";


void deserialize(char* json, PositionsList * posList);
void getNextPositions(long norad, uint16_t nbPos, PositionsList * posList);

#endif
