#include "Point.h"
#include <iostream>
#define PI 3.14159265
#pragma once
class Street
{
public:
	Street();
	~Street();

	static int instances;
	int streetID;
	int parentID;

	static Point getPointFromDistance(Point, float, int);

	void setPointA(float, float);
	void setPointB(float, float);
	void setPointC(float, float);

	void setDistance(float);
	void setSlope(int);
	void setAngleDirection(int);

	int getAngle();

	sf::Vertex getVertexA();
	sf::Vertex getVertexB();
	sf::Vertex getVertexC();

	Point getPointA();
	Point getPointB();
	Point getPointC();

	bool grow();

	void incrementDivisions();

	float calculateDistanceAB();
	float calculateDistanceAC();
	float calculateDistanceBC();

	void setMaxDivisions(int);
	int getNumbDivisions();

	int maxDistanceBetweenDivisions;

	bool containsChild(int);
	std::vector<int> childID;
private:
	Point pointA;
	Point pointB;
	Point pointC;

	int angleDir_;
	float distance_;
	int slope_;
	int numbDivisions_;
	int numbDivisionsMAX_;

	int calculateDistance(Point, Point);
};
