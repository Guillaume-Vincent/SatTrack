#include "WifiModule.h"


void wifiSetup(bool quiet) {
  if (!quiet) lcb.lcdPrintWifiConnection();
  WiFi.begin(HOTSPOT_SSID, HOTSPOT_PASS);

  uint8_t n = 5;
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() < t0 + 5000) {
    if (!quiet) {
      delay(500);
      lcb.lcdPrintChar(n++, 1, '.');
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!quiet) {
      lcb.lcdPrintWifiIP(WiFi.localIP());
      delay(2000);
    }
  }
  else {
    if (!quiet) {
      lcb.lcdPrintWifiFailed();
      for (int i=3; i>0; i--) {
        lcb.lcdPrintChar(10, 1, i + 48);
        delay(1000);
      }
    }
    wifiSetup(quiet);
  }
}


String buildRequest() {
  LiquidCrystalBoard::menu type = lcb.getSelectedMenu();
  const char* name = currentTargetList[lcb.getLcdPageSelected()].getName();
  long id = currentTargetList[lcb.getLcdPageSelected()].getID();

  String requestIP = "http://" + String(REMOTE_IP) + ":" + String(REMOTE_PORT) + "/";
  String requestParams;

  switch (type) {
    case LiquidCrystalBoard::menu::BODIES:
      requestParams = "bodypos/" + String(name) + "/";
      break;

    case LiquidCrystalBoard::menu::SATELLITES:
      requestParams = "satpos/" + String(id) + "/";
      break;

    case LiquidCrystalBoard::menu::STARS:
      requestParams = "starpos/" + String(id) + "/";
      break;

    default:
      break;
  }

  requestParams += String(OBS_LAT) + "/" + String(OBS_LONG) + "/" + String(OBS_ALT) + "/" + String(NB_OF_POSITIONS) + "/";
  
  return requestIP + requestParams;
}


void makeAPIRequest() {
  wifiSetup(true);
  String request = buildRequest();

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(request.c_str());

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();
      deserialize(payload);
    }
    else {
      // Serial.print("Error code: ");
      // Serial.println(httpResponseCode);
      // Serial.print("Request : ");
      // Serial.println(request);
    }

    http.end();
  }
  else {
    // Serial.println("WiFi Disconnected");
    lcb.resetLcd();
  }
  wifiSleep();
}

void wifiSleep() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();
  // Serial.println("Wifi Going To Sleep");
}
