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
	void setDistance(float); //setDistance prototype

	sf::Vertex getVertexA();
	sf::Vertex getVertexB();
	sf::Vertex getVertexC();

	Point getPointA();
	Point getPointB();

private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir;
	int density; //Population density rating of street
	float distance; //distance of line
	float distFromOrigin; //Distance from point of line origin

};

