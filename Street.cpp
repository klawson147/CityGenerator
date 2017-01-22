#include "Street.h"

int Street::instances = 0;

// param 1\ initial point
// param 2\ distance
// param 3\ angle
Point Street::getPointFromDistance(Point initialPoint, float distance, int angle)
{
	Point newPoint; //End point for new line

	newPoint.set_X((initialPoint.get_X()) + (distance * (float)cos(angle * PI / 180.0))); //Calculating new x coord
	newPoint.set_Y((initialPoint.get_Y()) + (distance * (float)sin(angle * PI / 180.0))); //Calculating new y coord

	return newPoint;
}

Street::Street()
{
	std::cout << "New Street [" << Street::instances << "]\n";
	numbDivisions_ = 0;
	maxDistanceBetweenDivisions = 25;
}

Street::~Street()
{
}

void Street::setPointA(float x, float y)
{
	pointA.set_X(x);
	pointA.set_Y(y);
}

void Street::setPointB(float x, float y)
{
	pointB.set_X(x);
	pointB.set_Y(y);
}

void Street::setPointC(float x, float y)
{
	pointC.set_X(x);
	pointC.set_Y(y);
}

sf::Vertex Street::getVertexA()
{
	sf::Vertex v;
	v.position.x = pointA.get_X();
	v.position.y = pointA.get_Y();
	return v;
}

sf::Vertex Street::getVertexB()
{
	sf::Vertex v;
	v.position.x = pointB.get_X();
	v.position.y = pointB.get_Y();
	return v;
}

sf::Vertex Street::getVertexC()
{
	sf::Vertex v;
	v.position.x = pointC.get_X();
	v.position.y = pointC.get_Y();
	return v;
}

Point Street::getPointA()
{
	return pointA;
}

Point Street::getPointB()
{
	return pointB;
}

Point Street::getPointC()
{
	return pointC;
}

void Street::setDistance(float dis)
{
	distance_ = dis;
}

void Street::setAngleDirection(int d)
{
	angleDir_ = d;
}

// Returns true if street still growing
// Returns false if street done growing
bool Street::grow()
{
	int distance = calculateDistance(pointB, pointC);

	if (distance <= 2)
	{
		pointB = pointC;
		return false;
	}
	else if (distance != 0)
	{
		pointB = getPointFromDistance(pointB, 1, angleDir_);
		return true;
	}

	return false;
}

void Street::setSlope(int s)
{
	slope_ = s;
}

int Street::calculateDistance(Point p1, Point p2)
{
	float distance;

	float xVec = (p2.get_X() - p1.get_X());
	float yVec = (p2.get_Y() - p1.get_Y());

	xVec *= xVec;
	yVec *= yVec;

	distance = xVec + yVec;
	distance = sqrt(distance);

	return distance;
}

float Street::calculateDistanceAB()
{
	return calculateDistance(pointA, pointB);
}

float Street::calculateDistanceAC()
{
	return calculateDistance(pointA, pointC);
}

float Street::calculateDistanceBC()
{
	return calculateDistance(pointB, pointC);
}

void Street::setMaxDivisions(int n)
{
	numbDivisionsMAX_ = n;
}

int Street::getNumbDivisions()
{
	return numbDivisions_;
}

int Street::getAngle()
{
	return angleDir_;
}

void Street::incrementDivisions()
{
	numbDivisions_++;
}

// Returns True if Street contains Child ID
bool Street::containsChild(int id)
{
	for (size_t i = 0; i < childID.size(); i++)
	{
		if (childID[i] == id)
			return true;
	}
	return false;
}