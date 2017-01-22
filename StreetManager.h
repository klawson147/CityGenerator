#include "StreetFactory.h"
#include "Point.h"
#include <vector>
#include <algorithm>
#pragma once
class StreetManager
{
public:

	StreetManager();
	StreetManager(sf::RenderWindow*);
	~StreetManager();

	void drawStreets();
	void setStartingPoint(sf::Vector2f);
	void timeStep();

	void createRandomLines(int);

	void setInitialStreet();

private:

	bool get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
		float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);

	bool get_line_intersection(Point, Point, Point, Point, float*, float*);

	Point startingPoint_;

	StreetFactory streetFactory;

	sf::RenderWindow* rw_;

	std::vector<Street> finishedStreets_;
	std::vector<Street> growingStreets_;

	void growStreets();
	void checkGlobalBounds();
	void checkLocalBounds();
	bool streetIntersects(Street, Street);
	Street createBranch(Street&);
};
