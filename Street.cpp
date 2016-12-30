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


sf::Vertex Street::getPointA()
{
	sf::Vertex v;
	v.position.x = pointA.get_X();
	v.position.y = pointA.get_Y();
	return v;
}

sf::Vertex Street::getPointB()
{
	sf::Vertex v;
	v.position.x = pointB.get_X();
	v.position.y = pointB.get_Y();
	return v;
}

void Street::setDistance(float dis) // setDistance function to assign distance var
{
	distance = dis;
}