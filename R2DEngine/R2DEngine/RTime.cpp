#include "RTime.h"

float rb::RTime::deltaTime;
float rb::RTime::elapsedTime;
float rb::RTime::lastFrameTime;

float rb::RTime::DeltaTime()
{
	return deltaTime;
}

float rb::RTime::ElapsedTime()
{
	return elapsedTime;
}

