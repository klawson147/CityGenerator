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
	Point p3;

	float slope = calculateSlope(p1, p2);

	int newX = getPossibleXValue(s1);

	float xVec = p1.get_X() - newX;

	slope *= xVec;
	slope -= p1.get_Y();


	return p3;
}

Street StreetFactory::getLineEndpoint(Point pLine, int distance, int angle)
{
	int newx, newy; //X coord and Y coord for new end point
	Point newPoint; //End point for new line
	Street newStreet; //Street to be returned

	newx = (pLine.get_X()) + (distance * cos(angle * PI / 180.0)); //Calculating new x coord
	newy = (pLine.get_Y()) + (distance * sin(angle * PI / 180.0)); //Calculating new y coord
	
	newPoint.set_X(newx); //Setting new end point x coord
	newPoint.set_Y(newy); //Setting new end point y coord
	
	newStreet.setPointC(newPoint.get_X(), newPoint.get_Y()); //Setting point C of street
	newStreet.setAngleDirection(angle); //Setting angle of street
	newStreet.setDistance(distance); //Setting distance of street

	return newStreet;
}

Street StreetFactory::getLineEndpoint(int x, int y, int distance, int angle)
{
	int newx, newy; //X coord and Y coord for new end point
	Point newPoint; //End point for new line
	Street newStreet; //Street to be returned

	newx = (x) + (distance * cos(angle * PI / 180.0)); //Calculating new x coord
	newy = (y) + (distance * sin(angle * PI / 180.0)); //Calculating new y coord

	newPoint.set_X(newx); //Setting new end point x coord
	newPoint.set_Y(newy); //Setting new end point y coord

	newStreet.setPointA(x, y);
	newStreet.setPointC(newPoint.get_X(), newPoint.get_Y()); //Setting point C of street
	newStreet.setAngleDirection(angle); //Setting angle of street
	newStreet.setDistance(distance); //Setting distance of street

	return newStreet;
}