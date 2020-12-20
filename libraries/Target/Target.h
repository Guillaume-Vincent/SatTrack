#ifndef TARGET_H
#define TARGET_H

#include "Constants.h"


class Target {
public:
	Target(const char* name);
	const char* getName() const;
	long getID() const;

protected:
	const char* name;
	long id;
};


class Body : public Target {
public:
	Body(const char* name);
};

class Satellite : public Target {
public:
	Satellite(const char* name, long norad);
};

class Star : public Target {
public:
	Star(const char* name, long hipparcos);
};



const int BODY_COUNT = 6;
const Body bodiesList[BODY_COUNT] = {
	Body(SUN),
	Body(VENUS),
	Body(MOON),
	Body(MARS),
	Body(JUPITER),
	Body(SATURN),
};


const int SAT_COUNT = 4;
const Satellite satellitesList[SAT_COUNT] = {
	Satellite(SPACE_STATION, 25544),
	Satellite(NOAA_19, 33591),
	Satellite(STARLINK_1517, 45787),
	Satellite(KRAKSAT, 44427),
};


const int STAR_COUNT = 11;
const Star starsList[STAR_COUNT] = {
	Star(SIRIUS, 32349),
	Star(ARCTURUS, 69673),
	Star(VEGA, 91262),
	Star(PROCYON, 37279),
	Star(BETELGEUSE, 27989),
	Star(ALTAIR, 97649),
	Star(ALDERBARAN, 21421),
	Star(ANTARES, 80763),
	Star(POLLUX, 37826),
	Star(CASTOR, 36850),
	Star(POLARIS, 11767),
};


#endif
