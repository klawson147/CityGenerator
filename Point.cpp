#include "Point.h"


Point::Point()
{
}


Point::Point(sf::Vector2i pos)
{
	position = pos;
}

Point::Point(int x, int y)
{
	position.x = x;
	position.y = y;
}

Point::~Point()
{
}

sf::Vector2i Point::getPosition()
{
	return position;
}

int Point::get_X()
{
	return position.x;
}

int Point::get_Y()
{
	return position.y;
}

void Point::set_X(int p)
{
	position.x = p;
}

void Point::set_Y(int p)
{
	position.y = p;
}