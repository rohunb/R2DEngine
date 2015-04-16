#ifndef R_CIRCLE_COLLIDER_H_
#define R_CIRCLE_COLLIDER_H_

#include "Collider.h"

namespace rb
{
	class CircleCollider : public Collider
	{
	public:
		CircleCollider();
		explicit CircleCollider(float radius);
		CircleCollider(const CircleCollider& rhs);
		CircleCollider& operator = (const CircleCollider& rhs);
		CircleCollider(CircleCollider&& rhs);
		CircleCollider& operator = (CircleCollider&& rhs);
		~CircleCollider() = default;

		float GetRadius() const;
		void SetRadius(float val);

		virtual std::unique_ptr<Collider> Clone() const override;

	private:
		float radius;
	};
}

#endif // R_CIRCLE_COLLIDER_H_
