#ifndef R_COLLIDER_H_
#define R_COLLIDER_H_

#include <functional>
#include "R2DComponent.h"
#include "GameConfig.h"

namespace rb
{
	class Collider : public R2DComponent
	{
	public:
		typedef std::function<void(Collider&)>  CollisionCallback;
		enum class ColliderType {Circle, Rect};

		Collider() = default;
		Collider(const Collider& rhs) = default;
		Collider& operator = (const Collider& rhs) = default;
		Collider(Collider&& rhs);
		Collider& operator = (Collider&& rhs);
		virtual ~Collider() = default;

		Collider::ColliderType GetType() const;
		virtual std::unique_ptr<Collider> Clone() const = 0;

		void RegisterCollisionCallback(const CollisionCallback& OnCollision);
		void OnCollisionEnter(Collider& otherCol);

	protected:
		ColliderType type;
		CollisionCallback OnCollision;
	};
}

#endif // R_COLLIDER_H_

