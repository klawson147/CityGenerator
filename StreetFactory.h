#include "Street.h"
#include "Directions.h"
#pragma once

#define PI 3.14159265

class StreetFactory
{
public:
	StreetFactory();
	~StreetFactory();

	Street getPerpLine(Point pLine, int a, int b);

private:


};

