#ifndef R_COLOUR_H_
#define R_COLOUR_H_

#include "RString.h"
#include "RVector.h"

namespace rb
{
	struct Colour
	{
		float r, g, b, a;

		Colour();
		Colour(float r, float g, float b);
		Colour(float r, float g, float b, float a);
		Colour(const Vec3& rgb);
		Colour(const Vec4& rgba);

		static Colour black;
		static Colour blue;
		static Colour clear;
		static Colour cyan;
		static Colour grey;
		static Colour green;
		static Colour magenta;
		static Colour red;
		static Colour white;
		static Colour yellow;

		string ToString();
		Vec4 ToVec4();

	};
}

#endif // R_COLOUR_H_
