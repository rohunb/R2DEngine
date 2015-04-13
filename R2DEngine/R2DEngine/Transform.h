#ifndef R_TRANSFORM_H_
#define R_TRANSFORM_H_

#include "R2DComponent.h"
#include "RVector.h"
#include "RMatrix.h"

namespace rb
{
	class Transform : public R2DComponent
	{
	public:
		Vec2 position;
		Vec2 size;
		float rotation;

		Transform();
		Transform(const Vec2& position, float rotation, const Vec2& size);

		void LookAt(const Vec2& targetPosition);
		Mat4 GetTransformMatrix() const;
	};
}
#endif // R_TRANSFORM_H_
