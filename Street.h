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

	__int16 streetID;
	__int16 parentID;

	Street* parent;

	void setColor(sf::Color);

	Point Street::getPointFromDistance(Point initialPoint, float distance, int angle);

	void setPointA(float, float);
	void setPointB(float, float);
	void setPointC(float, float);

	void setDistance(float);
	
	void setAngleDirection(int);

	int getAngle();

	sf::Vertex getVertexA();
	sf::Vertex getVertexB();
	sf::Vertex getVertexC();

	Point getPointA();
	Point getPointB();
	Point getPointC();

	bool grow();

	bool isMaster;
	bool shouldDivide;
	bool shouldDivideEnd;

	void incrementDivisions();

	//float calculateDistanceAB();
	float calculateDistanceAC();
	float calculateDistanceBC();

	void setMaxDivisions(int);
	int getNumbDivisions();

	int maxDistanceBetweenDivisions;

	bool containsChild(int);
	std::vector<__int16> childID;
private:
	Point pointA;
	Point pointB;
	Point pointC;

	__int16 angleDir_;
	//__int8 distance_;
	//__int8 numbDivisions_;
	
	sf::Color color;
	int calculateDistance(Point, Point);
};
