#ifndef R_SCREEN_H_
#define R_SCREEN_H_

#include "RVector.h"

namespace rb
{
	class Screen
	{
	public:
		int Width() const;
		int Height() const;
		static Vec2 ToWorldCoords(const Vec2& screenPosition);
	private:
		static int width;
		static int height;

		friend class R2DEngine;
	};
}

#endif // R_SCREEN_H_
