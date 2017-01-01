#include "SFML\Graphics.hpp"
#include <math.h>
#pragma once
class Point
{
public:
	Point();
	Point(sf::Vector2i);
	Point(int, int);
	~Point();

	int get_X();
	int get_Y();

	void set_X(int);
	void set_Y(int);

	sf::Vector2i getPosition();

private:
	sf::Vector2i position;

};

