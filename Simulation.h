#include <SFML/Graphics.hpp>
#include "StreetFactory.h"
#include "StreetManager.h"
#include <stdlib.h>
#include <time.h>
#include "Street.h"
#include <vector>
#include <iostream>
#include "Point.h"

#define MAX_FPS 60
#define SKIP_TICKS = 16.666
#define MAX_FRAMESKIP 10

#pragma once
class Simulation
{
public:
	Simulation();
	~Simulation();
	int startSimulation();
};

