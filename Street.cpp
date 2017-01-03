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

void Street::setDistance(float dis) // setDistance function to assign distance var
{
	distance = dis;
}

void Street::setAngleDirection(int d)
{
	angleDir = d;
}

// Returns true if street still growing
// Returns false if street done growing
bool Street::grow()
{
	int xb = pointB.get_X();
	int yb = pointB.get_Y();
	if (pointB.get_X() != pointC.get_X() || pointB.get_Y() != pointC.get_Y())
	{
		if (xb > pointC.get_X())
		{
			xb--;
			pointB.set_X(xb);
		}

		if (xb < pointC.get_X())
		{
			xb++;
			pointB.set_X(xb);
		}

		if (yb > pointC.get_Y())
		{
			yb--;
			pointB.set_Y(yb);

		}

		if (yb < pointC.get_Y())
		{
			yb++;
			pointB.set_Y(yb);

		}

		return true;
	}

	return false;

}

void Street::setSlope(int s)
{
	slope_ = s;
}