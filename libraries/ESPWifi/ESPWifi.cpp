#include "ESPWifi.h"


ESPWifi::ESPWifi(uint8_t rx, uint8_t tx)
: SoftwareSerial(rx, tx) {}

int ESPWifi::reset() {
	unsigned long t0;
	SoftwareSerial::println("AT+RST");
	
	t0 = millis();
	while (data != ready_str && millis() < t0 + 2000) {
    	while (SoftwareSerial::available()) {
    		data = SoftwareSerial::readStringUntil('\n');
  		}
  	}
  	if (data == ready_str) {
  		Serial.println("RESET DONE !");
  		return 0;
  	}
  	else {
  		Serial.println("Timeout");
  		return -1;
  	}
}
 
int ESPWifi::joinAccessPoint(String ssid, String pass) {
	unsigned long t0;
	String cwjap_command = String("AT+CWJAP=\"") + ssid + "\",\"" + pass + "\"";
	SoftwareSerial::println(cwjap_command);

	t0 = millis();
	while (data != ok_str && millis() < t0 + 2000) {
    	while (SoftwareSerial::available()) {
			data = SoftwareSerial::readStringUntil('\n');
    		if (data == "WIFI CONNECTED\r" || data == "WIFI GOT IP\r")
    			Serial.println(data);
    	}
  	}
  	return 0;
}

int ESPWifi::getLocalIP() {
	unsigned long t0;
	SoftwareSerial::println("AT+CIFSR");
	
	t0 = millis();
	while (millis() < t0 + 2000) {
		while (SoftwareSerial::available()) {
			data = SoftwareSerial::readStringUntil('"');
			if (data.startsWith("192.168.")) {
				Serial.println(data);
				return 0;
			}
		}
	}
	Serial.println("ESPWifi::getLocalIP() : Timeout");
	return -1;
}

int ESPWifi::establishConnection(String remoteIP, uint16_t remotePort) {
	unsigned long t0;
	String cipstart = "AT+CIPSTART=\"TCP\",\"" + remoteIP + "\"," + String(remotePort);
	SoftwareSerial::println(cipstart);
	
	t0 = millis();
	while (data != ok_str && millis() < t0 + 2000) {
		while (SoftwareSerial::available()) {
			data = SoftwareSerial::readStringUntil('\n');
			if (data == "CONNECT\r") {
				Serial.println("Connected to 192.168.43.1:5000");
				return 0;
			}
		}
	}
	Serial.println("ESPWifi::establishConnection() : Timeout");
	return -1;
}
