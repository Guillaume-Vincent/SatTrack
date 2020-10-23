#include "Tools.h"


int getLength(char* str) {
	int i = 0;
	while (str[i++] != '\0');
	return i-1;
}
