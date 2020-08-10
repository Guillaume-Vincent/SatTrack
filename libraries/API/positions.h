#ifndef POSITIONS_H
#define POSITIONS_H

#include "Arduino.h"


class Position {
	friend class PositionsList;

public:
	Position(float azimuth, float elevation);

	float getAzimuth();
	float getElevation();
	bool isNextNull();

protected:
	float azimuth;
	float elevation;
	Position * next;
};


class PositionsList {
public:
	PositionsList();

	void addPosition(float azimuth, float elevation);
	bool isEmpty();
	Position * getNext();
	int getNbPositions();
	void clearList();

protected:
	Position * first;
	Position * last;
	int nbPositions;
};


#endif
