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
	float m;
	float deltaY = (float)p2.get_Y() - (float)p1.get_Y();
	float deltaX = (float)p2.get_X() - (float)p1.get_X();

	m = deltaY / deltaX;
	
	return m;
}

// Return a Random X Value in the Range of a Street
float StreetFactory::getPossibleXValue(Street s1)
{
	if (s1.getPointA().get_X() > s1.getPointB().get_X())
	{
		return getUniformRandomInRange(s1.getPointB().get_X(), s1.getPointA().get_X());
	}
	else
	{
		return getUniformRandomInRange(s1.getPointA().get_X(), s1.getPointB().get_X());
	}
}

// Return a Random Point on the Street s1
Point StreetFactory::getPointOnLine(Street s1)
{
	Point p1 = s1.getPointA();
	Point p2 = s1.getPointB();
	Point p3;

	float slope = calculateSlope(p1, p2);

	float newX = getPossibleXValue(s1);
	
	float xVec = p1.get_X() - newX;

	slope *= xVec;
	slope -= p1.get_Y();
	slope *= -1; //4th Quadrant Environment
	p3.set_X(newX);
	p3.set_Y(slope);

	return p3;
}
// Return a Point on the Street s1 at position x
// no error checking
Point StreetFactory::getPointOnLine(Street s1, float newX)
{
	Point p1 = s1.getPointA();
	Point p2 = s1.getPointB();
	Point p3;

	float slope = calculateSlope(p1, p2);
	float xVec = p1.get_X() - newX;

	slope *= xVec;
	slope -= p1.get_Y();
	slope *= -1; //4th Quadant Environment
	p3.set_X(newX);
	p3.set_Y(slope);

	return p3;
}


// args: initial point, distance, angle
Street StreetFactory::createStreetFromPoint(Point pLine, float distance, float angle)
{
	angle *= -1; // 4th Quadrant Environment

	float newx, newy; //X coord and Y coord for new end point
	Point newPoint; //End point for new line
	Street newStreet; //Street to be returned

	newx = (pLine.get_X()) + (distance * (float)cos(angle * PI / 180.0)); //Calculating new x coord
	newy = (pLine.get_Y()) + (distance * (float)sin(angle * PI / 180.0)); //Calculating new y coord

	newPoint.set_X(newx); //Setting new end point x coord
	newPoint.set_Y(newy); //Setting new end point y coord
	
	newStreet.setPointA(pLine.get_X(), pLine.get_Y());
	newStreet.setPointB(pLine.get_X(), pLine.get_Y());
	newStreet.setPointC(newPoint.get_X(), newPoint.get_Y()); //Setting point C of street

	newStreet.setSlope(calculateSlope(newStreet.getPointA(), newStreet.getPointC()));
	newStreet.setAngleDirection(angle); //Setting angle of street
	newStreet.setDistance(distance); //Setting distance of street

	return newStreet;
}
// args: initial x, initial y, distance, angle
Street StreetFactory::createStreetFromPoint(float x, float y, float distance, float angle)
{
	angle *= -1; // 4th Quadrant Environment

	float newx, newy; //X coord and Y coord for new end point
	Point newPoint; //End point for new line
	Street newStreet; //Street to be returned

	newx = (x) + (distance * cos(angle * PI / 180.0)); //Calculating new x coord
	newy = (y) + (distance * sin(angle * PI / 180.0)); //Calculating new y coord
	
	newPoint.set_X(newx); //Setting new end point x coord
	newPoint.set_Y(newy); //Setting new end point y coord

	newStreet.setPointA(x, y);
	newStreet.setPointB(x, y);
	newStreet.setPointC(newPoint.get_X(), newPoint.get_Y()); //Setting point C of street

	newStreet.setAngleDirection(angle); //Setting angle of street
	newStreet.setDistance(distance); //Setting distance of street

	return newStreet;
}


float StreetFactory::getRandomAngle()
{	
	return getUniformRandomInRange(0, 359);
}

Street StreetFactory::createRandomStreet(sf::Vector2i lb, sf::Vector2i up)
{
	Street newStreet;
	
	float x1 = rand() % (up.x - lb.x) + (lb.x);
	float y1 = rand() % (up.y - lb.y) + (lb.y);

	float x2 = rand() % (up.x - lb.x) + (lb.x);
	float y2 = rand() % (up.y - lb.y) + (lb.y);

	newStreet.setPointA(x1, y1);
	newStreet.setPointB(x2, y2);
	newStreet.setPointC(x2, y2);

	return newStreet;
}

// Get a random perpendicular angle
float StreetFactory::getPerpendicularAngle(float angle)
{
	int result = getUniformRandomInRange(0, 1);

	if (result == 1)
	{
		angle += 90;

		if (angle > 359)
		{
			angle -= 359;
			return angle;
		}
	}
	else
	{
		angle -= 90;

		if (angle < 0)
		{
			angle = 360 + angle;
			return angle;
		}
	}
	return angle;
}

// Get a perpendicular angle
//  1  positive
// -1  negative
float StreetFactory::getPerpendicularAngle(float angle, float direction)
{
	int perp = (90 * direction);

	angle += perp;

	if (angle > 359)
	{
		angle -= 359;
		return angle;
	}

	if (angle < 0)
	{
		angle = 360 + angle;
		return angle;
	}
	return angle;
}

// Return a random number in range of lower - upper
// Uniform Probability
float StreetFactory::getUniformRandomInRange(float lower, float upper)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(lower, upper);

	return dis(gen);
}