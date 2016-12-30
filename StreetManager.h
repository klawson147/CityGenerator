#include "StreetFactory.h"
#include <vector>
#pragma once
class StreetManager
{
public:
	StreetManager();
	~StreetManager();

	


private:
	void setStartingPoint(sf::Vector2i);
	void timeStep();


	std::vector<Street> streets;
};

