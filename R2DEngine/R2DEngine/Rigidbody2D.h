#ifndef R_RIGIDBODY_2D_H_
#define R_RIGIDBODY_2D_H_

#include "R2DComponent.h"
#include "RVector.h"

namespace rb
{
	class Rigidbody2D: public R2DComponent
	{
	public:
		Vec2 velocity;

		Rigidbody2D();
		explicit Rigidbody2D(const Vec2& velocity);

		void Update(float dt);

	};
}

#endif // R_RIGIDBODY_2D_H_
