#ifndef SATELLITES_H
#define SATELLITES_H


class Satellite {
public:
	Satellite(char* name, long norad);

	char* getName();
	long getNorad();

private:
	char* name;
	long norad;
};


const int satNumber = 4;

const Satellite satList[satNumber + 1] = {
	Satellite("Space Station", 25544),
	Satellite("NOAA 19", 33591),
	Satellite("STARLINK-1517", 45787),
	Satellite("KRAKSAT", 44427),

	Satellite("STOP", 0)
};


#endif
