#include "Point.h"
#define PI 3.14159265
#pragma once
class Street
{
public:
	Street();
	~Street();

	static Point getPointFromDistance(Point, float, int);

	void setPointA(float, float);
	void setPointB(float, float);
	void setPointC(float, float);

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

	sf::Color* getColor();

private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir;
	float distance_;

	float calculateDistance(Point, Point);

	sf::Color* color_;

	int slope_;

};

