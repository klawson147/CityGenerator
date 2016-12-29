#include "Point.h"

#pragma once
class Street
{
public:
	Street();
	~Street();

	void setPointA(int, int);
	void setPointB(int, int);
	void setPointC(int, int);

	sf::Vertex getPointA();
	sf::Vertex getPointB();

private:
	Point pointA;
	Point pointB;
	Point pointC;

};

