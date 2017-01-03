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
	void setDistance(float); 

	void setSlope(int);

	sf::Vertex getVertexA();
	sf::Vertex getVertexB();
	sf::Vertex getVertexC();

	Point getPointA();
	Point getPointB();

	bool grow();

private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir;
	
	float distanceB;
	float distanceC;

	float distance; //distance of line
	float distFromOrigin; //Distance from point of line origin

	int slope_;

};

