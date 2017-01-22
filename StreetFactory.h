#include <math.h>
#include <time.h>
#include <random>
#include "Street.h"
#include "Directions.h"
#include <iostream>
#include "Point.h"
#pragma once

#define PI 3.14159265

class StreetFactory
{
public:
	StreetFactory();
	~StreetFactory();

	Street createStreetFromPoint(Point, float, float);
	Street createStreetFromPoint(float, float, float, float);

	Street createRandomStreet(sf::Vector2i, sf::Vector2i);

	Street createStreetDivision(Street);

	float calculateSlope(Point, Point);
	float getPossibleXValue(Street);

	float getRandomAngle();

	float getPerpendicularAngle(float);
	float getPerpendicularAngle(float, float);

	Point getPointOnLine(Street);
	Point getPointOnLine(Street, float);

	float getUniformRandomInRange(float, float);

	bool pointIntersects(Point, Point, Point);
private:
};
