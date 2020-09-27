#include "ESPWifi.h"


ESPWifi::ESPWifi(uint8_t rx, uint8_t tx)
: SoftwareSerial(rx, tx) {}

void ESPWifi::init() {
	Serial.print(ESP_INIT);
	if (reset() && joinAccessPoint()) Serial.println(ESP_DONE);
	else Serial.println(ESP_FAILED);
}

bool ESPWifi::reset() {
	String data = "";
	SoftwareSerial::println("AT+RST");
	
	unsigned long t0 = millis();
	while (data != ready_str && millis() < t0 + 1000) {
    	while (SoftwareSerial::available()) {
    		data = SoftwareSerial::readStringUntil('\n');
  		}
  	}
  	return data == ready_str;
}

bool ESPWifi::joinAccessPoint() {
	bool connected = false;
	bool gotip = false;
	String data = "";

	char cwjapCommand[41];
	sprintf(cwjapCommand, "AT+CWJAP=\"%s\",\"%s\"", hotspot_ssid, hotspot_pass);
	SoftwareSerial::println(cwjapCommand);

	unsigned long t0 = millis();
	while (data != ok_str && millis() < t0 + 10000) {
    	while (SoftwareSerial::available()) {
			data = SoftwareSerial::readStringUntil('\n');
    		if (data == connected_str) connected = true;
    		if (data == gotip_str) gotip = true;
  		}
  	}
  	return data == ok_str && connected && gotip;
}

bool ESPWifi::establishConnection() {
	Serial.print(ESP_CONN);
	bool connected = false;
	String data = "";

	char cipstartCommand[38];
	sprintf(cipstartCommand, "AT+CIPSTART=\"TCP\",\"%s\",%s", remote_ip, remote_port);
	SoftwareSerial::println(cipstartCommand);

	unsigned long t0 = millis();
	while (data != ok_str && millis() < t0 + 1000) {
		while (SoftwareSerial::available()) {
			data = SoftwareSerial::readStringUntil('\n');
			if (data == connect_str) connected = true;
		}
	}
	if (data == ok_str && connected) {
		Serial.println(ESP_DONE);
		return true;
	}
	else {
		Serial.println(ESP_FAILED);
		return false;
	}
}

void ESPWifi::makeAPIRequest(long norad) {
	int j = 0;
	int k = 0;
	char databyte;
	bool jsonFound = false;
	String data = "";

	char getCommand[51];
	char hostCommad[22];
	char cipsendCommand[14];
	sprintf(getCommand, "GET /satpos/%ld/%s/%s/%d/%d/ HTTP/1.1", norad, OBS_LAT, OBS_LONG, OBS_ALT, NB_OF_POSITIONS);
	sprintf(hostCommad, "Host: %s\r\n", remote_ip);
	sprintf(cipsendCommand, "AT+CIPSEND=%d", getLength(getCommand) + getLength(hostCommad) + 4);
	
	SoftwareSerial::println(cipsendCommand);
	delay(50);
	SoftwareSerial::println(getCommand);
	SoftwareSerial::println(hostCommad);
	unsigned long t0 = millis();
	
	while (!jsonFound && millis() < t0 + 10000) {	
		while (SoftwareSerial::available() && j++ < 15) {
			data = SoftwareSerial::readStringUntil('\n');
		}
		while (SoftwareSerial::available() && j >= 15 && !jsonFound) {
			databyte = SoftwareSerial::read();
			jsonData[k] = databyte;
			jsonFound = (databyte == '}');
			k++;
		}
	}
	deserialize(jsonData);
}
