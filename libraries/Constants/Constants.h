#ifndef CONSTANTS_H
#define CONSTANTS_H


#include "Arduino.h"
#ifdef ARDUINO_ARCH_AVR
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif


/* WIFIMODULE.H */
// Request Settings
const uint8_t NB_OF_POSITIONS = 60;

// Wifi Settings
// const char HOTSPOT_SSID[] PROGMEM = "SatTrackHotspot";
// const char HOTSPOT_PASS[] PROGMEM = "SatTrackPwd";
// const char HOTSPOT_SSID[] PROGMEM = "SFR_E3B0";
// const char HOTSPOT_PASS[] PROGMEM = "du6rtgRaxxla";
const char HOTSPOT_SSID[] PROGMEM = "NETGEAR35";
const char HOTSPOT_PASS[] PROGMEM = "breezybreeze287";
const char REMOTE_IP[] PROGMEM = "192.168.0.42";
const char REMOTE_PORT[] PROGMEM = "5000";


/* API.H */
// Observator Location
// const char OBS_LAT[] PROGMEM  = "48.755"; // Antony Lat
// const char OBS_LONG[] PROGMEM = "2.283";  // Antony Long
// const uint16_t OBS_ALT = 88;              // Antony Alt
const char OBS_LAT[] PROGMEM  = "43.573"; // Toulouse Lat
const char OBS_LONG[] PROGMEM = "1.469";  // Toulouse Long
const uint16_t OBS_ALT = 151;             // Toulouse Alt
const uint16_t JSON_MAX_SIZE = 13 + 14 * NB_OF_POSITIONS + 1;


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
// Pins
const uint8_t d4 = 26;
const uint8_t d5 = 25;
const uint8_t d6 = 33;
const uint8_t d7 = 32;
const uint8_t rs_lcd = 4;
const uint8_t en_lcd = 16;
const uint8_t bl_lcd = 17;
const uint8_t btn = 36;

// Menus
const int MENU_COUNT = 3;
const char BODIES_TEXT[] PROGMEM = 		"<    Bodies    >";
const char SATELLITES_TEXT[] PROGMEM = 	"<  Satellites  >";
const char STARS_TEXT[] PROGMEM = 		"<    Stars     >";

// LCD
const char LCD_VOID[] PROGMEM = 		"                ";
const char LCD_WELCOME0[] PROGMEM = 	" -- SatTrack -- ";
const char LCD_WELCOME1[] PROGMEM = 	" v1.0 - Dec2020 ";
const char LCD_INITIALIZING[] PROGMEM = " Initializing : ";
const char LCD_WIFI32[] PROGMEM =		" Wifi           ";
const char LCD_WIFICONNECT[] PROGMEM =	" Wifi Connected ";
const char LCD_WIFI_FAILED[] PROGMEM = 	" Wifi - FAILED  ";
const char LCD_WIFIRETRY[] PROGMEM =	" Retry In       ";
const char LCD_TESTING[] PROGMEM = 		" Testing :      ";
const char LCD_SERVO[] PROGMEM = 		" Servo - ...    ";
const char LCD_SERVO_DONE[] PROGMEM = 	" Servo - DONE   ";
const char LCD_STEPPER[] PROGMEM = 		" Stepper - ...  ";
const char LCD_STEPPER_DONE[] PROGMEM = " Stepper - DONE ";
const char LCD_STEPPER_TEST[] PROGMEM = " Stepper - TEST ";

//Buttons
const uint8_t DEBOUNCE_COUNTER = 50;


/* STEPPERMOTOR.H */
// Pins
const uint8_t dir_stp = 18;
const uint8_t step_stp = 19;
const uint8_t en_stp = 27;

// Ratio and speed
const float gear_ratio = 0.1413;
const uint16_t pulse_delay = 300;

#endif
