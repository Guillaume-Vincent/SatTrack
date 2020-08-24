#include "Satellites.h"


Satellite::Satellite(const char* name, long norad)
: name(name), norad(norad) {}

const char* Satellite::getName() const {
	return name;
}

long Satellite::getNorad() const {
	return norad;
}
