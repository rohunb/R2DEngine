#include "RRandom.h"

std::random_device rb::Random::randomDevice;
std::mt19937 rb::Random::randomEngine(randomDevice());

float rb::Random::UnitFloat()
{
	return RangeFromZero(1.0f);
}
float rb::Random::RangeFromZero(float max)
{
	return Range(0.0f, max);
}
float rb::Random::Range(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(randomEngine);
}
rb::Vec2 rb::Random::UnitVector()
{
	return Vec2(Range(-1.0f, 1.0f), Range(-1.0f, 1.0f));
}




