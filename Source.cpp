#include <windows.h>
#include "Simulation.h"
#include <tchar.h>

int main()
{
	// Let Windows know this Process should be run as the highest priority
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	Simulation simulation;
	return simulation.startSimulation();
}

