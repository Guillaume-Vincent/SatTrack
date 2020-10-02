#include "Target.h"


Target::Target(const char* name)
: name(name), id(0) {}

const char* Target::getName() const {
	return name;
}

long Target::getID() const {
	return id;
}


Body::Body(const char* name)
: Target(name) {}

Satellite::Satellite(const char* name, long norad)
: Target(name) {
	id = norad;
}

Star::Star(const char* name, long hipparcos)
: Target(name) {
	id = hipparcos;	
}
