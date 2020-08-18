#ifndef ESPWIFI_H
#define ESPWIFI_H

#include "Arduino.h"
#include <SoftwareSerial.h>


const String ok_str = "OK\r";
const String data = "";
const String ready_str = "ready\r";


class ESPWifi : public SoftwareSerial {
public:
	ESPWifi(uint8_t rx, uint8_t tx);

	int reset();
	int joinAccessPoint(String ssid, String pass);
	int getLocalIP();
	int establishConnection(String remoteIP, uint16_t remotePort);
};


#endif
