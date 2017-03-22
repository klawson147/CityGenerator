#include "Simulation.h"

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

int Simulation::startSimulation()
{
	srand(time(NULL));

	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Default, cs);
	window.setFramerateLimit(60);

	StreetManager streetManager(&window);

	streetManager.setStartingPoint(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	streetManager.setInitialStreet();

	sf::Clock clock;
	sf::Clock permClock;

	unsigned long next_game_tick = permClock.getElapsedTime().asMilliseconds();

	int loops;
	bool isPaused = false;
	bool isSpaceDown = false;

	bool shouldDraw = true;
	bool isQDOwn = false;

	sf::View view1(sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920, 1080));
	window.setView(view1);

	while (window.isOpen())
	{
		loops = 0;

		// Update Simulation
		while (clock.getElapsedTime().asMilliseconds() > next_game_tick && loops < MAX_FPS)
		{
			if (!isPaused)
			{
				streetManager.timeStep();
			}

			sf::Event event;
			// Poll for Events
			while (window.pollEvent(event))
			{
				window.setKeyRepeatEnabled(true);
				if (event.type == sf::Event::Resized)
				{
					// update the view to the new size of the window
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}

				// Close Window Event
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type = sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						streetManager.setInitialStreet();
					}

					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}

					// Pause Simulation
					if (event.key.code == sf::Keyboard::Space)
					{
						if (isSpaceDown)
						{
							isSpaceDown = false;
						}
						else
						{
							if (isPaused)
								isPaused = false;
							else
								isPaused = true;
							isSpaceDown = true;
						}
					}

					if (event.key.code == sf::Keyboard::Left)
					{
						view1.zoom(0.9f);
						
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						view1.zoom(1.1);
						
					}
					if (event.key.code == sf::Keyboard::W)
					{
						view1.move(0, -25);
						
					}
					if (event.key.code == sf::Keyboard::S)
					{
						view1.move(0, 25);
					}
					if (event.key.code == sf::Keyboard::A)
					{
						view1.move(-25, 0);
					}
					if (event.key.code == sf::Keyboard::D)
					{
						view1.move(25, 0);
					}

					if (event.key.code == sf::Keyboard::Q)
					{
						if (isQDOwn)
						{
							isQDOwn = false;
						}
						else
						{

							if (shouldDraw)
								shouldDraw = false;
							else
								shouldDraw = true;
							isQDOwn = true;
						}



					}

					// Update View
					window.setView(view1);
				}
			}

			next_game_tick += (unsigned long)16.666;
			loops++;
		}
		// Draw Simulation
		window.clear(sf::Color::White);
		if (shouldDraw)
			streetManager.drawStreets();
		window.display();
	}

	return 0;
}