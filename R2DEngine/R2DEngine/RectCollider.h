#ifndef R_RECT_COLLIDER_H_
#define R_RECT_COLLIDER_H_

#include "Collider.h"

namespace rb
{
	class RectCollider : public Collider
	{
	public:

		virtual std::unique_ptr<Collider> Clone() const override;

	};
}


#endif // R_RECT_COLLIDER_H_
