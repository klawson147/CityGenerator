#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{
}

RandomNumberGenerator::~RandomNumberGenerator()
{
}

// Return a random number in range of lower - upper
// Uniform Probability
float RandomNumberGenerator::getUniformRandomInRange(float lower, float upper)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(lower, upper);

	return dis(gen);
}

// Return a random number in range of lower - upper
// Uniform Probability
int RandomNumberGenerator::getUniformRandomInRange(int lower, int upper)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(lower, upper);

	return dis(gen);
}

// Returns a number in range (0-359)
int RandomNumberGenerator::getUniformRandomAngle()
{
	return getUniformRandomInRange(0, 359);
}

// Return a Random 45 Angle (0, 45, 90, 135, 180, 225, 270, 315)
int RandomNumberGenerator::GetUniformRandom45Angle()
{
	return getUniformRandomInRange(0, 7) * 45;
}

// Return a Random 90 Angle (0, 90, 180, 270)
int RandomNumberGenerator::GetUniformRandom90Angle()
{
	return getUniformRandomInRange(0, 3) * 90;
}

// Return a Random 45 Angle (0, 45, 90, 135, 180, 225, 270, 315)
// Angle will not be the same or inverse of parent angle
int RandomNumberGenerator::GetUniformRandom45Angle(int parentAngle)
{
	int newAngle;
	int inverseAngle;

	if (parentAngle < 0)
		parentAngle *= -1;

	if (parentAngle < 180)
		inverseAngle = parentAngle + 180;
	else
		inverseAngle = parentAngle - 180;

	do
	{
		newAngle = getUniformRandomInRange(0, 7) * 45;
	} while ((newAngle == parentAngle) || (newAngle == inverseAngle));

	return newAngle;
}
// Return a Random 90 Angle (0, 90, 180, 270)
// Angle will not be the same or inverse of parent angle
int RandomNumberGenerator::GetUniformRandom90Angle(int parentAngle)
{
	int newAngle;
	int inverseAngle;

	if (parentAngle < 0)
		parentAngle *= -1;

	if (parentAngle < 180)
		inverseAngle = parentAngle + 180;
	else
		inverseAngle = parentAngle - 180;

	do
	{
		newAngle = getUniformRandomInRange(0, 3) * 90;
	} while ((newAngle == parentAngle) || (newAngle == inverseAngle));

	return newAngle;
}

int RandomNumberGenerator::getUniformRandomAngle(int parentAngle)
{
	int newAngle;
	int inverseAngle;

	if (parentAngle < 0)
		parentAngle *= -1;

	if (parentAngle < 180)
		inverseAngle = parentAngle + 180;
	else
		inverseAngle = parentAngle - 180;

	do
	{
		newAngle = getUniformRandomInRange(0, 359);
	} while ((newAngle == parentAngle) || (newAngle == inverseAngle));

	return newAngle;
}