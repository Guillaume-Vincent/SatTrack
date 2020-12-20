#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include "Arduino.h"
#include "API.h"
#include "Constants.h"
#include <esp_wifi.h>
#include <HTTPClient.h>
#include "LiquidCrystalBoard.h"
#include "Target.h"


extern LiquidCrystalBoard lcb;
extern const Target * currentTargetList;


void wifiSetup(bool quiet);
String buildRequest();
void makeAPIRequest();
void wifiSleep();


#endif
