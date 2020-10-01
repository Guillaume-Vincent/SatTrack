#ifndef ESPWIFI_H
#define ESPWIFI_H

#include "Arduino.h"
#include "API.h"
#include "Constants.h"
#include "LiquidCrystalBoard.h"
#include "Tools.h"
#include <SoftwareSerial.h>


extern char jsonData[];
extern LiquidCrystalBoard lcb;

const String ok_str = "OK\r";
const String ready_str = "ready\r";
const String closed_str = "CLOSED\r";
const String connect_str = "CONNECT\r";
const String connected_str = "WIFI CONNECTED\r";
const String gotip_str = "WIFI GOT IP\r";


class ESPWifi : public SoftwareSerial {
public:
	ESPWifi(uint8_t rx, uint8_t tx);
	void init();

	bool reset();
	bool joinAccessPoint();
	bool establishConnection();
	void makeAPIRequest(long norad, enum LiquidCrystalBoard::menu type);
};


#endif
