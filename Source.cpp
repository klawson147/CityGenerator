#include <SFML/Graphics.hpp>
#include "StreetFactory.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Street.h"
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
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(850, 850), "SFML works!", sf::Style::Default, cs);
	window.setFramerateLimit(5);

	Street InitialStreet;
	Street s2;
	std::vector<Street> GrowingStreets;
	std::vector<Street> FinishedStreets;

	StreetFactory streetFactory;

	//FinishedStreets.push_back(streetFactory.createStreetFromPoint(50, 50, 300, 90));
	//FinishedStreets.push_back(streetFactory.createStreetFromPoint(200, 450, 300, -120));

	Street s1;
	s1.setPointA(22, 150);
	s1.setPointB(700, 700);
	s1.setPointC(700, 700);

	FinishedStreets.push_back(s1);
	s1.setPointA(50, 500);
	s1.setPointB(500, 50);
	s1.setPointC(500, 50);
	
	FinishedStreets.push_back(s1);

	sf::Clock clock;
	float lastTime = 0;

	while (window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime - lastTime);
		lastTime = currentTime;
		std::cout << lastTime << std::endl;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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
	
	StreetFactory streetFactory;

	

	for (auto i = st.begin(); i != st.end(); i++)
	{
	
		va.append(i->getVertexA());
		va.append(i->getVertexC());
		rw.draw(va);

		Point t;
		for (int q = 0; q < 20; q++)
		{

			t = streetFactory.getPointOnLine(*i);
			intersectionShape.setFillColor(sf::Color::Red);
			//std::cout << "X: " << t.get_X() << " Y: " << t.get_Y() << std::endl;
			intersectionShape.setPosition(t.get_X() - 5, t.get_Y() - 5);
			rw.draw(intersectionShape);
		}
		
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
					intersectionShape.setFillColor(sf::Color::Blue);
					intersectionShape.setPosition(*xinter - 5, *yinter - 5);
					rw.draw(intersectionShape);
					
				}
				else
				{
					
				}
			}
			
		}


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

