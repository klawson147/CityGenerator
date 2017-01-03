#include <math.h>
#include <time.h>
#include <random>
#include "Street.h"
#include "Directions.h"
#include "Point.h"
#pragma once

#define PI 3.14159265

class StreetFactory
{
public:
	StreetFactory();
	~StreetFactory();

	Street createStreetFromPoint(Point, int, int);
	Street createStreetFromPoint(int, int, int, int);

	Street createRandomStreet(sf::Vector2i, sf::Vector2i);

	float calculateSlope(Point, Point);
	int getPossibleXValue(Street);

	int getRandomAngle();

	int getPerpendicularAngle(int);
	int getPerpendicularAngle(int, int);

	Point getPointOnLine(Street);
	Point getPointOnLine(Street, int);
private:

	int getUniformRandomInRange(int, int);
	
	
	
};

