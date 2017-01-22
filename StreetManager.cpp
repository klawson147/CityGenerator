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

void StreetManager::setStartingPoint(sf::Vector2f position)
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

bool StreetManager::get_line_intersection(Point p1, Point p2, Point p3, Point p4, float *i_x, float *i_y)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p2.get_X() - p1.get_X();     s1_y = (p2.get_Y() - p1.get_Y());
	s2_x = p4.get_X() - p3.get_X();     s2_y = (p4.get_Y() - p3.get_Y());

	float s, t;
	s = (-s1_y * (p1.get_X() - p3.get_X()) + s1_x * (p1.get_Y() - p3.get_Y())) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p1.get_Y() - p3.get_Y()) - s2_y * (p1.get_X() - p3.get_X())) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = p1.get_X() + (t * s1_x);
		if (i_y != NULL)
			*i_y = p1.get_Y() + (t * s1_y);
		return true;
	}
	return false; // No collision
}

void StreetManager::setInitialStreet()
{
	growingStreets_.clear();
	finishedStreets_.clear();
	Street::instances = 0;

	Street temp;
	for (int i = 0; i < 1; i++)
	{
		temp = streetFactory.createStreetFromPoint(400, 399, 2000, 90);
		temp.parentID = -1;
		temp.streetID = Street::instances;
		Street::instances++;
		growingStreets_.push_back(temp);

		temp = streetFactory.createStreetFromPoint(400, 401, 2000, 270);
		temp.parentID = -1;
		temp.streetID = Street::instances;
		Street::instances++;
		growingStreets_.push_back(temp);

		temp = streetFactory.createStreetFromPoint(399, 400, 2000, 180);
		temp.parentID = -1;
		temp.streetID = Street::instances;
		Street::instances++;
		growingStreets_.push_back(temp);

		temp = streetFactory.createStreetFromPoint(401, 400, 2000, 0);
		temp.parentID = -1;
		temp.streetID = Street::instances;
		Street::instances++;
		growingStreets_.push_back(temp);
	}
}

void StreetManager::timeStep()
{
	growStreets();
	checkGlobalBounds();
	checkLocalBounds();

	for (size_t i = 0; i < growingStreets_.size(); i++)
	{
		growingStreets_[i].maxDistanceBetweenDivisions--;

		if (growingStreets_[i].getNumbDivisions() < 4)
		{
			if (streetFactory.getUniformRandomInRange(1, 100) == 1 && growingStreets_[i].maxDistanceBetweenDivisions < 0)
			{
				Street temp;

				growingStreets_[i].maxDistanceBetweenDivisions = 25;
				growingStreets_[i].incrementDivisions();

				temp = streetFactory.createStreetDivision(growingStreets_[i]);
				temp.parentID = growingStreets_[i].streetID;
				temp.streetID = Street::instances;
				Street::instances++;

				growingStreets_[i].childID.push_back(temp.streetID);
				growingStreets_.push_back(temp);
			}
		}
	}
}

void StreetManager::growStreets()
{
	for (std::size_t i = 0; i != growingStreets_.size(); i++)
	{
		if (growingStreets_.at(i).grow() == false)
		{
			finishedStreets_.push_back(growingStreets_.at(i));
			growingStreets_.erase(growingStreets_.begin() + i);
		}
	}
}

void StreetManager::checkGlobalBounds()
{
reset3:
	for (int i = 0; i < growingStreets_.size(); i++)
	{
		if (growingStreets_.at(i).getPointB().get_X() >= 800 ||
			growingStreets_.at(i).getPointB().get_X() <= 0 ||
			growingStreets_.at(i).getPointB().get_Y() <= 0 ||
			growingStreets_.at(i).getPointB().get_Y() >= 600)
		{
			finishedStreets_.push_back(growingStreets_.at(i));
			growingStreets_.erase(growingStreets_.begin() + i);
			goto reset3;
		}
	}
}

void StreetManager::checkLocalBounds()
{
	bool resetFlag = false;

reset1:
	for (int i = 0; i < growingStreets_.size(); i++)
	{
		for (int g = 0; g < growingStreets_.size(); g++)
		{
			// Not Same Street
			// Not Parent Street
			if (streetIntersects(growingStreets_[i], growingStreets_[g]))
			{
				finishedStreets_.push_back(growingStreets_.at(i));
				growingStreets_.erase(growingStreets_.begin() + i);

				// Oh God
				goto reset1;
			}
		}
	}

reset2:
	for (int t = 0; t < growingStreets_.size(); t++)
	{
		for (int f = 0; f < finishedStreets_.size(); f++)
		{
			if (streetIntersects(growingStreets_[t], finishedStreets_[f]))
			{
				finishedStreets_.push_back(growingStreets_.at(t));
				growingStreets_.erase(growingStreets_.begin() + t);

				// Oh God
				goto reset2;
			}
		}
	}
}

// Return True if A intersects B
// Filters out Parents
// Filters out Same Street
// Filters out Children
bool StreetManager::streetIntersects(Street A, Street B)
{
	if (A.parentID != B.streetID &&
		A.streetID != B.streetID &&
		(!A.containsChild(B.streetID)))
	{
		if (get_line_intersection(A.getPointA(), A.getPointB(), B.getPointA(), B.getPointB(), new float, new float))
		{
			return true;
		}
	}

	return false;
}