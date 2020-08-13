#include "Satellites.h"


Satellite::Satellite(char* name, long norad)
: name(name), norad(norad) {}

char* Satellite::getName() {
	return name;
}

long Satellite::getNorad() {
	return norad;
}
