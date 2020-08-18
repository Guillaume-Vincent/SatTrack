#include "API.h"


void deserialize(const char* json, PositionsList * posList) {
	StaticJsonDocument<350> doc;

	DeserializationError error = deserializeJson(doc, (const __FlashStringHelper*)json);

	if (error) {
    	Serial.print(F("deserializeJson() failed: "));
    	Serial.println(error.c_str());
    	return;
    }

    const char* satname = doc["N"];
    long satid = doc["I"];
    uint16_t nbpos = doc["S"];

    Serial.print(satname);
    Serial.print(" (");
    Serial.print(satid);
    Serial.println(")");

    for (uint16_t i=1; i<nbpos; i++){
    	posList->addPosition(doc["A"][i], doc["E"][i]);
    }
}

void getNextPositions(long norad, uint16_t nbPos, PositionsList * posList) {
	String API_REQUEST = API_BASE_URL + norad + OBS_DATA + nbPos + "/";
	Serial.print("API REQUEST GET : ");
	Serial.println(API_REQUEST);

	delay(750);
	
	switch (norad){
		case 25544:
			deserialize(input1, posList);
			break;
		case 33591:
			deserialize(input2, posList);
			break;
		case 45787:
			deserialize(input3, posList);
			break;
		case 44427:
			deserialize(input4, posList);
		default:
			break;
	}
}
