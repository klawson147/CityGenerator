#include "StreetFactory.h"


StreetFactory::StreetFactory()
{
}


StreetFactory::~StreetFactory()
{
}

Street getPerpLine(Point pLine, int distance, int angle)
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