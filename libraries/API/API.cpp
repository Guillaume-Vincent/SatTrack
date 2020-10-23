#include "API.h"


void deserialize(String payload) {
	char datastr[JSON_MAX_SIZE];
	payload.toCharArray(datastr, JSON_MAX_SIZE);
	deserialize(datastr);
}

void deserialize(char* datastr) {
	int i;
	int j = 0;
	char strBuffer[7];
	int intBuffer;

	float azimuth = 0.0;
	float elevation = 0.0;

	for (i=1; datastr[i] != '\0'; i++) {
		switch (datastr[i]) {
			case ',':
				strBuffer[j] = '\0';
				j = 0;	
				sscanf(strBuffer, "%d", &intBuffer);
				azimuth = intBuffer / 100.0;
				break;

			case '}':
			case ';':
				strBuffer[j] = '\0';
				j = 0;
				sscanf(strBuffer, "%d", &intBuffer);
				elevation = intBuffer / 100.0;

				posList->addPosition(azimuth, elevation);
				break;

			default:
				strBuffer[j] = datastr[i];
				j++;
				break;
		}
	}
}
