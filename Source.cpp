#include <SFML/Graphics.hpp>
#include "StreetFactory.h"
#include "StreetManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Street.h"
#include <vector>
#include <iostream>
#include "Point.h"

#define MAX_FPS 60
#define SKIP_TICKS = 16.666
#define MAX_FRAMESKIP 10

int main()
{
	srand(time(NULL));

	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, cs);
	window.setFramerateLimit(60);

	StreetManager streetManager(&window);

	streetManager.setStartingPoint(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	streetManager.setInitialStreet();

	sf::Clock clock;
	sf::Clock permClock;

	unsigned long next_game_tick = permClock.getElapsedTime().asMilliseconds();

	int loops;

	while (window.isOpen())
	{
		loops = 0;

		// Update Simulation
		while (clock.getElapsedTime().asMilliseconds() > next_game_tick && loops < MAX_FPS)
		{
			streetManager.timeStep();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type = sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						streetManager.setInitialStreet();
					}
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
				}
			}

			next_game_tick += (unsigned long)16.666;
			loops++;
		}
		// Draw Simulation
		window.clear();
		streetManager.drawStreets();
		window.display();
	}

	return 0;
}