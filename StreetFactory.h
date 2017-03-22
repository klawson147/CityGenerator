#include <math.h>
#include <time.h>
#include "Street.h"
#include "Directions.h"
#include <iostream>
#include "Point.h"
#include "RandomNumberGenerator.h"
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
	Street createStreetDivision(Street, int);

private:
	float calculateSlope(Point, Point);
	float getPossibleXValue(Street);
	float getRandomAngle();

	float getPerpendicularAngle(float);
	float getPerpendicularAngle(float, float);
	double getAngleBetweenTwoPoints(Point, Point);

	Point getPointOnLine(Street);
	Point getPointOnLine(Street, float);

	float getUniformRandomInRange(float, float);

	bool pointIntersects(Point, Point, Point);
};
