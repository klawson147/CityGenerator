#include "SFML\Graphics.hpp"
#include <math.h>
#include <vector>
#pragma once
class Point
{
public:
	Point();
	Point(sf::Vector2f);
	Point(float, float);
	~Point();

	float get_X();
	float get_Y();

	void set_X(float);
	void set_Y(float);

	sf::Vector2f getPosition();

private:
	sf::Vector2f position;

};

