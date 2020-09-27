#ifndef ESPWIFI_H
#define ESPWIFI_H

#include "Arduino.h"
#include "API.h"
#include "Tools.h"
#include <SoftwareSerial.h>


extern char jsonData[];

const char hotspot_ssid[] = "SatTrackHotspot";
const char hotspot_pass[] = "SatTrackPwd";

const char remote_ip[] = "192.168.43.1";
const char remote_port[] = "5000";

const String ok_str = "OK\r";
const String ready_str = "ready\r";
const String closed_str = "CLOSED\r";
const String connect_str = "CONNECT\r";
const String connected_str = "WIFI CONNECTED\r";
const String gotip_str = "WIFI GOT IP\r";

const char ESP_INIT[] = "ESP8266 Initialization  : ";
const char ESP_CONN[] = "Establishing Connection : ";
const char ESP_DONE[] = "Done";
const char ESP_FAILED[] = "Failed";


class ESPWifi : public SoftwareSerial {
public:
	ESPWifi(uint8_t rx, uint8_t tx);
	void init();

	bool reset();
	bool joinAccessPoint();
	bool establishConnection();
	void makeAPIRequest(long norad);
};


#endif
