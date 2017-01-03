#include "StreetManager.h"


StreetManager::StreetManager(sf::RenderWindow* rw)
{
	rw_ = rw;
}


StreetManager::~StreetManager()
{
}

void StreetManager::drawStreets()
{
	sf::VertexArray va;
	va.setPrimitiveType(sf::Lines);

	for (auto i = finishedStreets_.begin(); i != finishedStreets_.end(); i++)
	{
		va.append(i->getVertexA());
		va.append(i->getVertexB());
		rw_->draw(va);
		va.clear();
	}

	for (auto i = growingStreets_.begin(); i != growingStreets_.end(); i++)
	{
		va.append(i->getVertexA());
		va.append(i->getVertexB());
		rw_->draw(va);
		va.clear();
	}
}


void StreetManager::setStartingPoint(sf::Vector2i position)
{
	startingPoint_.set_X(position.x);
	startingPoint_.set_Y(position.y);
}

void StreetManager::createRandomLines(int n)
{
	finishedStreets_.clear();
	for (int i = 0; i < n; i++)
	{
		finishedStreets_.push_back(streetFactory.createRandomStreet(sf::Vector2i(0, 0), sf::Vector2i(rw_->getSize().x, rw_->getSize().y)));
	}
}

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
bool StreetManager::get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
	float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;     s1_y = (p1_y - p0_y);
	s2_x = p3_x - p2_x;     s2_y = (p3_y - p2_y);

	float s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = p0_x + (t * s1_x);
		if (i_y != NULL)
			*i_y = p0_y + (t * s1_y);
		return true;
	}

	return false; // No collision
}



void StreetManager::setInitialStreet()
{
	finishedStreets_.clear();
	growingStreets_.clear();

	for (int i = 0; i < 15; i++)
	{
		growingStreets_.push_back(streetFactory.createStreetFromPoint(startingPoint_, 400, streetFactory.getRandomAngle()));
	}
	
	

}



void StreetManager::timeStep()
{
	for (int i = 0; i < growingStreets_.size(); i++)
	{
		if (growingStreets_[i].grow() == false)
		{
			finishedStreets_.push_back(growingStreets_.at(i));
			growingStreets_.erase(growingStreets_.begin() + i);
			
		}
		
		
	}

	//growingStreets_.push_back(streetFactory.)
}