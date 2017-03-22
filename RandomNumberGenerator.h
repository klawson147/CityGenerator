#include <random>
#pragma once
class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	~RandomNumberGenerator();

	static float getUniformRandomInRange(float, float);
	static int getUniformRandomInRange(int, int);
	static int getUniformRandomAngle();
	static int GetUniformRandom45Angle();
	static int GetUniformRandom90Angle();

	static int getUniformRandomAngle(int);
	static int GetUniformRandom45Angle(int);
	static int GetUniformRandom90Angle(int);
};
