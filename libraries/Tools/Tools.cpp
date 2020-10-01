#include "Tools.h"


uint16_t angleToPeriod(float angle, uint16_t minPosPeriod, uint16_t maxPosPeriod) {
    return 0.5 + (angle + 90.0) * (maxPosPeriod - minPosPeriod) / 180.0 + minPosPeriod;
}

int getLength(char* str) {
	int i = 0;
	while (str[i++] != '\0');
	return i-1;
}
