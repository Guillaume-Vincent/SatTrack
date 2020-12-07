#include "Tools.h"


int getLength(char* str) {
	int i = 0;
	while (str[i++] != '\0');
	return i-1;
}

int mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
	float map = (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
	return (int)(map + 0.5);
}
