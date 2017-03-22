#include "Point.h"

Point::Point()
{
}

Point::Point(sf::Vector2f pos)
{
	position = pos;
}

Point::Point(float x, float y)
{
	position.x = x;
	position.y = y;
}

Point::~Point()
{
}

sf::Vector2f Point::getPosition()
{
	return position;
}

float Point::get_X()
{
	return position.x;
}

float Point::get_Y()
{
	return position.y;
}

void Point::set_X(float p)
{
	position.x = p;
}

void Point::set_Y(float p)
{
	position.y = p;
}