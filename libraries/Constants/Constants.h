#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <avr/pgmspace.h>



/* API.H */
// Observator Location
const char OBS_LAT[] PROGMEM  = "48.755"; // Antony Lat
const char OBS_LONG[] PROGMEM = "2.283";  // Antony Long
const char OBS_ALT[] PROGMEM  = "88";      // Antony Alt
// const char OBS_LAT[] PROGMEM  = "43.573"; // Toulouse Lat
// const char OBS_LONG[] PROGMEM = "1.469";  // Toulouse Long
// const char OBS_ALT[] PROGMEM  = 151;     // AntToulouseony Alt


/* SATELLITES.H */
// Satellites
const char SPACE_STATION[] PROGMEM = "Space Station";
const char NOAA_19[] PROGMEM = "NOAA 19";
const char STARLINK_1517[] PROGMEM = "STARLINK-1517";
const char KRAKSAT[] PROGMEM = "KRAKSAT";

// Stars
const char SIRIUS[] PROGMEM = "Sirius";
const char ARCTURUS[] PROGMEM = "Arcturus";
const char VEGA[] PROGMEM = "Vega";
const char PROCYON[] PROGMEM = "Procyon";
const char BETELGEUSE[] PROGMEM = "Betelgeuse";
const char ALTAIR[] PROGMEM = "Altair";
const char ALDERBARAN[] PROGMEM = "Aldebaran";
const char ANTARES[] PROGMEM = "Antares";
const char POLLUX[] PROGMEM = "Pollux";
const char CASTOR[] PROGMEM = "Castor";
const char POLARIS[] PROGMEM = "Polaris";

// Bodies
const char SUN[] PROGMEM = "Sun";
const char VENUS[] PROGMEM = "Venus";
const char MOON[] PROGMEM = "Moon";
const char MARS[] PROGMEM = "Mars";
const char JUPITER[] PROGMEM = "Jupiter";
const char SATURN[] PROGMEM = "Saturn";


/* LCD.H */
// Menus
const char BODIES_TEXT[] PROGMEM = 		"<    Bodies    >";
const char SATELLITES_TEXT[] PROGMEM = 	"<  Satellites  >";
const char STARS_TEXT[] PROGMEM = 		"<    Stars     >";

// LCD
const char LCD_VOID[] PROGMEM = 		"                ";
const char LCD_WELCOME0[] PROGMEM = 	" -- SatTrack -- ";
const char LCD_WELCOME1[] PROGMEM = 	" v1.0 - Oct2020 ";
const char LCD_INITIALIZING[] PROGMEM = " Initializing : ";
const char LCD_ESP8266[] PROGMEM = 		" ESP8266 - ...  ";
const char LCD_WIFI_FAILED[] PROGMEM = 	" Wifi - FAILED  ";
const char LCD_WIFI_SUCCESS[] PROGMEM = " Wifi - SUCCESS ";
const char LCD_SERVO[] PROGMEM = 		" Servo - ...    ";
const char LCD_SERVO_DONE[] PROGMEM = 	" Servo - DONE   ";
const char LCD_TESTING[] PROGMEM = 		" Testing :      ";
const char LCD_STEPPER[] PROGMEM = 		" Stepper - ...  ";
const char LCD_STEPPER_DONE[] PROGMEM = " Stepper - DONE ";


/* ESPWIFI.H */
// Wifi Settings
const char HOTSPOT_SSID[] PROGMEM = "SatTrackHotspot";
const char HOTSPOT_PASS[] PROGMEM = "SatTrackPwd";
const char REMOTE_IP[] PROGMEM = "192.168.43.1";
const char REMOTE_PORT[] PROGMEM = "5000";

// ESP Serial communication (to be replaced)
const char ESP_CONN[] PROGMEM = "Establishing Connection : ";
const char ESP_DONE[] PROGMEM = "Done";
const char ESP_FAILED[] PROGMEM = "Failed";


// AT Commands
const char AT_RST[] PROGMEM = "AT+RST";

#endif
