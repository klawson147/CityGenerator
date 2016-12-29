#include "Point.h"

#pragma once
class Street
{
public:
	Street();
	~Street();


	void setAngleDirection(int);
	void setPointA(int, int);
	void setPointB(int, int);
	void setPointC(int, int);

	int density;
	float distFromOrigin;

	sf::Vertex getPointA();
	sf::Vertex getPointB();

private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir;

};

