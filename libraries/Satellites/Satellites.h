#ifndef SATELLITES_H
#define SATELLITES_H


class Satellite {
public:
	Satellite(const char* name, long norad);

	const char* getName() const;
	long getNorad() const;

private:
	const char* name;
	long norad;
};


const int SAT_COUNT = 4;
const Satellite satList[SAT_COUNT] = {
	Satellite("Space Station", 25544),
	Satellite("NOAA 19", 33591),
	Satellite("STARLINK-1517", 45787),
	Satellite("KRAKSAT", 44427),
};


#endif
