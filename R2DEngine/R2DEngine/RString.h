#ifndef R_STRING_H_
#define R_STRING_H_

#include <string>
#include "RVector.h"

namespace rb
{
	using string = std::string;
	
	string ToString(float value);
	string ToString(double value);
	string ToString(int value);
	string ToString(unsigned int value);
	string ToString(bool value);

	string ToString(const Vec2& vec);
}
#endif // !R_STRING_H_
