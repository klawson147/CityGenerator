#include "StreetManager.h"

StreetManager::StreetManager(sf::RenderWindow* rw)
{
	rw_ = rw;
	executionCount = 0;

	intersectionPointX = new float;
	intersectionPointY = new float;
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

// Returns 1 if the lines intersect, otherwise 0. If the lines
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

bool StreetManager::get_line_intersection(Point p1, Point p2, Point p3, Point p4)
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
		*intersectionPointX = p1.get_X() + (t * s1_x);
		*intersectionPointY = p1.get_Y() + (t * s1_y);
		return true;
	}
	return false; // No collision
}

void StreetManager::setInitialStreet()
{
	growingStreets_.clear();
	finishedStreets_.clear();

	growingStreets_.reserve(1000);
	finishedStreets_.reserve(12000);

	Street::instances = 0;

	Street temp;

	for (int i = 0; i < 15; i++)
	{
		temp = streetFactory.createStreetFromPoint(rw_->getSize().x / 2, rw_->getSize().y / 2, 2000, i*(360 / 15));
		temp.isMaster = true;
		temp.parentID = -1;
		temp.streetID = Street::instances++;
		//temp.setPointB(temp.getPointC().get_X(), temp.getPointC().get_Y());
		temp.setColor(GROWING_COLOR);

		if (streetWillIntersect(temp))
		{
			temp.shouldDivideEnd = false;
			temp.setPointC(*intersectionPointX, *intersectionPointY);
		}

		growingStreets_.push_back(temp);
	}


	/*
	for (int i = 0; i < 15; i++)
	{
	temp = streetFactory.createStreetFromPoint((rw_->getSize().x / 2) + (i * (1000/15)), rw_->getSize().y / 2, 1000, 270);
	temp.isMaster = true;
	temp.parentID = -1;
	temp.streetID = Street::instances++;
	//temp.setPointB(temp.getPointC().get_X(), temp.getPointC().get_Y());
	temp.setColor(sf::Color::Green);

	if (streetWillIntersect(temp))
	{
	temp.shouldDivideEnd = false;
	temp.setPointC(*intersectionPointX, *intersectionPointY);
	}

	growingStreets_.push_back(temp);
	}
	for (int i = 0; i < 15; i++)
	{
	temp = streetFactory.createStreetFromPoint((rw_->getSize().x / 2), (rw_->getSize().y / 2)  +(i * (1000 / 15)), 1000, 0);
	temp.isMaster = true;
	temp.parentID = -1;
	temp.streetID = Street::instances++;
	//temp.setPointB(temp.getPointC().get_X(), temp.getPointC().get_Y());
	temp.setColor(sf::Color::Green);

	if (streetWillIntersect(temp))
	{
	temp.shouldDivideEnd = false;
	temp.setPointC(*intersectionPointX, *intersectionPointY);
	}

	growingStreets_.push_back(temp);
	}*/
}

void StreetManager::timeStep()
{
	std::cout << growingStreets_.size() + finishedStreets_.size() << std::endl;
	growStreets();

	divideStreets();
}

void StreetManager::divideStreets()
{
	for (size_t i = 0; i < growingStreets_.size(); i++)
	{
		growingStreets_[i].maxDistanceBetweenDivisions--;

		if (RandomNumberGenerator::getUniformRandomInRange(1, 25) == 1 && growingStreets_[i].maxDistanceBetweenDivisions < 0)
		{
			if (growingStreets_[i].shouldDivide == true)
			{
				// If street is not close to completion
				if (growingStreets_[i].calculateDistanceBC() < (growingStreets_[i].calculateDistanceAC() - 30))
				{
					Street temp;

					growingStreets_[i].maxDistanceBetweenDivisions = 30;

					temp = streetFactory.createStreetDivision(growingStreets_[i], Street::instances++);
					growingStreets_[i].childID.push_back(Street::instances);

					if (streetWillIntersect(temp))
					{
						temp.shouldDivideEnd = false;
						temp.setPointC(*intersectionPointX, *intersectionPointY);
					}
					growingStreets_.push_back(temp);
				}
			}
		}
	}
}

void StreetManager::growStreets()
{
	for (std::size_t i = 0; i < growingStreets_.size(); i++)
	{
		if (growingStreets_.at(i).grow() == false)
		{
			if (growingStreets_[i].shouldDivideEnd == true)
			{
				// Create New Street at end of Finished Street
				Street temp = streetFactory.createStreetDivision(growingStreets_[i], Street::instances);
				growingStreets_[i].childID.push_back(temp.streetID);

				if (streetWillIntersect(temp))
				{
					temp.shouldDivideEnd = false;
					temp.setPointC(*intersectionPointX, *intersectionPointY);
				}

				growingStreets_.push_back(temp);
			}

			// Move Street to Finished Vector
			growingStreets_.at(i).setColor(FINISHED_COLOR);
			finishedStreets_.push_back(growingStreets_.at(i));
			growingStreets_.erase(growingStreets_.begin() + i);
			Street::instances++;
		}
	}
}

void StreetManager::checkGlobalBounds()
{
	for (std::vector<Street>::iterator it = growingStreets_.begin(); it != growingStreets_.end(); it++)
	{
		if (it->getPointB().get_X() >= rw_->getSize().x ||
			it->getPointB().get_X() <= 0 ||
			it->getPointB().get_Y() <= 0 ||
			it->getPointB().get_Y() >= rw_->getSize().y)
		{
			it->setColor(FINISHED_COLOR);
			finishedStreets_.push_back(*it);
			growingStreets_.erase(it);

			it = growingStreets_.begin();
		}
	}
}

void StreetManager::checkLocalBounds()
{
reset1:
	for (int i = 0; i < growingStreets_.size(); i++)
	{
		for (int g = 0; g < growingStreets_.size(); g++)
		{
			// Not Same Street
			// Not Parent Street
			if (streetIntersects(growingStreets_[i], growingStreets_[g]))
			{
				growingStreets_.at(i).setColor(FINISHED_COLOR);
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
				growingStreets_.at(t).setColor(FINISHED_COLOR);
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
// Filters out Master Streets
bool StreetManager::streetIntersects(Street A, Street B)
{
	if (A.parentID == B.streetID || A.streetID == B.parentID || A.streetID == B.streetID || (A.isMaster && B.isMaster))
		return false;

	if (!A.containsChild(B.streetID))
	{
		if (get_line_intersection(A.getPointA(), A.getPointC(), B.getPointA(), B.getPointC()))
		{
			return true;
		}
	}

	return false;
}

bool StreetManager::streetWillIntersect(Street s)
{
	std::vector<sf::Vector2f> intersectionPoints;

	for (std::vector<Street>::iterator it = growingStreets_.begin(); it != growingStreets_.end(); it++)
	{
		if (streetIntersects(s, *it))
		{
			intersectionPoints.push_back(sf::Vector2f(*intersectionPointX, *intersectionPointY));
		}
	}

	for (std::vector<Street>::iterator it = finishedStreets_.begin(); it != finishedStreets_.end(); it++)
	{
		if (streetIntersects(s, *it))
		{
			intersectionPoints.push_back(sf::Vector2f(*intersectionPointX, *intersectionPointY));
		}
	}

	if (!intersectionPoints.empty())
	{
		int d = INT_MAX;

		float x2, x1, y2, y1;
		x1 = s.getPointA().get_X();
		y1 = s.getPointA().get_Y();

		for (std::vector<sf::Vector2f>::iterator it = intersectionPoints.begin(); it != intersectionPoints.end(); it++)
		{
			x2 = it->x;
			y2 = it->y;

			if (std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2)) < d)
			{
				d = std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
				*intersectionPointX = x2;
				*intersectionPointY = y2;
			}
		}

		return true;
	}

	return false;
}