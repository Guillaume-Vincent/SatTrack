#include "API.h"


void deserialize(char* datastr) {
	int i, j;
	char strBuffer[7];
	int intBuffer;

	float azimuth;
	float elevation;

	for (i=0; datastr[i] != '\0'; i++) {
		switch (datastr[i]) {
			case '{':
				j = 0;
				break;

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
