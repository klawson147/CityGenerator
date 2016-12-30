#include "Street.h"


Street::Street()
{
}


Street::~Street()
{
}


void Street::setPointA(int x, int y)
{
	pointA.set_X(x);
	pointA.set_Y(y);
}

void Street::setPointB(int x, int y)
{
	pointB.set_X(x);
	pointB.set_Y(y);
}

void Street::setPointC(int x, int y)
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

Point Street::getPointA()
{
	return pointA;
}

Point Street::getPointB()
{
	return pointB;
}

void Street::setDistance(float dis) // setDistance function to assign distance var
{
	distance = dis;
}