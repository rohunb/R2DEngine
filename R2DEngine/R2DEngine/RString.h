#ifndef R_STRING_H_
#define R_STRING_H_

#include <string>

namespace rb
{
	using string = std::string;
	string ToString(float value);
	string ToString(int value);
	string ToString(bool value);
}
#endif // !R_STRING_H_
