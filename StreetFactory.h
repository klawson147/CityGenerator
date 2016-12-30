#include <math.h>
#include <time.h>
#include "Street.h"
#include "Directions.h"
#include "Point.h"
#pragma once


class StreetFactory
{
public:
	StreetFactory();
	~StreetFactory();


private:

	Point getPointOnLine(Street);
	float calculateSlope(Point, Point);
	int getPossibleXValue(Street);
};

