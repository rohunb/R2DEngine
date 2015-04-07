#ifndef R_R2D_COMPONENT_H_
#define R_R2D_COMPONENT_H_

#include "RMemory.h"

namespace rb
{
	class R2DComponent
	{
	public:
		R2DComponent();
		R2DComponent(const R2DComponent& rhs);
		R2DComponent(R2DComponent&& rhs);
		R2DComponent& operator = (const R2DComponent& rhs);
		R2DComponent& operator = (R2DComponent&& rhs);
		virtual ~R2DComponent();

		class GameObject& GetGameObject() const;
		class Transform& GetTransform() const;

	protected:
		SharedPtr<class GameObject> gameObject;
		SharedPtr<class Transform> transform;
	};
}

#endif // !R_R2D_COMPONENT_H_
