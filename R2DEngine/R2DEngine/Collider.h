#ifndef R_COLLIDER_H_
#define R_COLLIDER_H_

#include "R2DComponent.h"
#include "GameConfig.h"

namespace rb
{
	class Collider : public R2DComponent
	{
	public:
		Collider() = default;
		Collider(const Collider& rhs) = default;
		Collider& operator = (const Collider& rhs) = default;
		Collider(Collider&& rhs);
		Collider& operator = (Collider&& rhs);
		virtual ~Collider() = default;

		virtual std::unique_ptr<Collider> Clone() const = 0;
		virtual void Init();

	protected:
	};
}

#endif // R_COLLIDER_H_

