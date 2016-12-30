#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Street.h"
#include "StreetFactory.h"
#include <vector>
#include <iostream>
#include "Point.h"

#define NUMBSTREETS
bool get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
	float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
void renderer(sf::RenderWindow& rw, std::vector<Street>& st);
int main()
{

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(850, 850), "SFML works!");
	window.setFramerateLimit(60);

	Street InitialStreet;
	std::vector<Street> GrowingStreets;
	std::vector<Street> FinishedStreets;

	StreetFactory streetFactory;
	Point p;
	p.set_X(50);
	p.set_Y(50);
	InitialStreet = streetFactory.getLineEndpoint(p, 22, 25);
	FinishedStreets.push_back(InitialStreet);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					
				}
			}
		}
	
		window.clear();
		renderer(window, FinishedStreets);
		window.display();
	}

	return 0;
}

void renderer(sf::RenderWindow& rw, std::vector<Street>& st)
{
	float* xinter = new float(0.0);
	float* yinter = new float(0.0);

	sf::CircleShape intersectionShape(5);
	intersectionShape.setFillColor(sf::Color::Red);

	sf::VertexArray va;
	sf::Vertex v;
	v.color = sf::Color::Blue;
	va.setPrimitiveType(sf::Lines);

	for (auto i = st.begin(); i != st.end(); i++)
	{
		va.append(i->getVertexA());
		va.append(i->getVertexC());
		rw.draw(va);

		/*
		for (auto t = st.begin(); t != st.end(); t++)
		{
			if (t != i)
			{
				if (get_line_intersection(
					i->getVertexA().position.x, i->getVertexA().position.y,
					i->getVertexC().position.x, i->getVertexC().position.y,
					t->getVertexA().position.x, t->getVertexA().position.y,
					t->getVertexC().position.x, t->getVertexC().position.y,
					xinter, yinter))
				{
					intersectionShape.setPosition(*xinter - 5, *yinter - 5);
					rw.draw(intersectionShape);
					std::cout << "Intersection\n";
				}
				else
				{
					std::cout << "Not\n";
				}
			}
			
		}*/


	}
}



// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
bool get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
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

