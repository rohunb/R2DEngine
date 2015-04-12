#ifndef R_RANDOM_H_
#define R_RANDOM_H_

#include <random>
#include "RVector.h"

namespace rb
{
	class Random
	{
	public:
		static float UnitFloat();
		static float Range(float min, float max);
		static float RangeFromZero(float max);
		static Vec2 UnitVector();
	private:
		static std::random_device randomDevice;
		static std::mt19937 randomEngine;
	};
}

#endif // R_RANDOM_H_
