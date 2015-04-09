#include "RString.h"

using namespace std;
using namespace rb;

std::string rb::ToString(float num)
{
	return std::to_string(num);
}

std::string rb::ToString(bool value)
{
	return to_string(value);
}

std::string rb::ToString(int value)
{
	return to_string(value);
}
std::string rb::ToString(unsigned int value)
{
	return to_string(value);
}
