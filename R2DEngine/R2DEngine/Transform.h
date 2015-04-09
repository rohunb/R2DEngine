#ifndef R_TRANSFORM_H_
#define R_TRANSFORM_H_

#include "R2DComponent.h"
#include "RVector.h"

namespace rb
{
	class Transform : public R2DComponent
	{
	public:
		Vec2 position;
		Vec2 size;
		float rotation;

		Transform();
		Transform(const Vec2& position, const Vec2& size, float rotation);
	};
}
#endif // R_TRANSFORM_H_
