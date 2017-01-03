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

	void setDistance(float); 
	void setSlope(int);
	void setAngleDirection(int);

	sf::Vertex getVertexA();
	sf::Vertex getVertexB();
	sf::Vertex getVertexC();

	Point getPointA();
	Point getPointB();
	Point getPointC();

	bool grow();

private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir;
	
	float distance; //distance of line
	float distFromOrigin; //Distance from point of line origin

	int slope_;

};

