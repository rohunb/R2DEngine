#ifndef R_SCREEN_H_
#define R_SCREEN_H_

#include "RVector.h"

namespace rb
{
	class Screen
	{
	public:
		static int Width();
		static int Height();
		static float WidthToFloat();
		static float HeightToFloat();
		static Vec2 Center();
		static Vec2 ToWorldCoords(const Vec2& screenPosition);
	private:
		static int width;
		static int height;

		friend class R2DEngine;
	};
}

#endif // R_SCREEN_H_
