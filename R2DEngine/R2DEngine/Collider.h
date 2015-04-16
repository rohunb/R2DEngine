#ifndef R_COLLIDER_H_
#define R_COLLIDER_H_

#include "R2DComponent.h"
#include "GameConfig.h"

namespace rb
{
	class Collider : public R2DComponent
	{
	public:
		enum class ColliderType {Circle, Rect};

		Collider() = default;
		Collider(const Collider& rhs) = default;
		Collider& operator = (const Collider& rhs) = default;
		Collider(Collider&& rhs);
		Collider& operator = (Collider&& rhs);
		virtual ~Collider() = default;

		Collider::ColliderType GetType() const;
		virtual std::unique_ptr<Collider> Clone() const = 0;

	protected:
		ColliderType type;
	};
}

#endif // R_COLLIDER_H_

