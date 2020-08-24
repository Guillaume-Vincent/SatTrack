#include "Positions.h"


Position::Position(float azimuth, float elevation)
: azimuth(azimuth), elevation(elevation), next(NULL) {}

float Position::getAzimuth() {
	return azimuth;
}

float Position::getElevation() {
	return elevation;
}

bool Position::isNextNull() {
	return next == NULL;
}


PositionsList::PositionsList()
:first(NULL), last(NULL), nbPositions(0) {}

void PositionsList::addPosition(float azimuth, float elevation) {
	if (nbPositions == 0) {
		first = new Position(azimuth, elevation);
		last = first;
	}
	else {
		last->next = new Position(azimuth, elevation);
		last = last->next;
	}
	nbPositions ++;
}

bool PositionsList::isEmpty() {
	return nbPositions == 0;
}

Position * PositionsList::getNext() {
	if (nbPositions > 0) {
		Position * pos = first;
		first = first->next;

		nbPositions --;

		return pos;
	}
}

int PositionsList::getNbPositions() {
	return nbPositions;
}

void PositionsList::clearList() {
	Position * removeCurr = first;
	Position * removeNext;

	while (removeCurr != NULL) {
		removeNext = removeCurr->next;
		delete removeCurr;
		removeCurr = removeNext;
		nbPositions --;
	}

	first = NULL;
	last = NULL;
}
