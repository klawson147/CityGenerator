#include "StreetFactory.h"


StreetFactory::StreetFactory()
{
}


StreetFactory::~StreetFactory()
{
}



// Return The Slope from 2 Points
float StreetFactory::calculateSlope(Point p1, Point p2)
{
	float m = p1.get_Y() - p2.get_Y();
	m /= (p1.get_X() - p2.get_X());
	return m;
}

// Return a Random X Value in the Range of a Street
int StreetFactory::getPossibleXValue(Street s1)
{
	srand(time(NULL));

	int xValue;

	if (s1.getPointA().get_X() > s1.getPointB().get_X())
	{
		xValue = rand() % s1.getPointA().get_X() + s1.getPointB().get_X();
	}
	else
	{
		xValue = rand() % s1.getPointB().get_X() + s1.getPointA().get_X();
	}

	return xValue;

}

// Return a Random Point on the Street s1
Point StreetFactory::getPointOnLine(Street s1)
{
	Point p1 = s1.getPointA();
	Point p2 = s1.getPointB();

	float slope = calculateSlope(p1, p2);

	int newX = getPossibleXValue(s1);

	float xVec = p1.get_X() - newX;

	slope *= xVec;
	slope -= p1.get_Y();

}