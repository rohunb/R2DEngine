#ifndef R_R2D_COMPONENT_H_
#define R_R2D_COMPONENT_H_

#include <memory>

namespace rb
{
	class R2DComponent
	{
	public:
		//ctors
		R2DComponent();
		R2DComponent(const R2DComponent& rhs);
		R2DComponent(R2DComponent&& rhs);
		R2DComponent& operator = (const R2DComponent& rhs);
		R2DComponent& operator = (R2DComponent&& rhs);
		virtual ~R2DComponent();

		std::shared_ptr<class GameObject> GetGameObject() const;
		
	protected:
		std::shared_ptr<class GameObject> gameObject;

	private:
		friend class GameObject;
	};
}

#endif // !R_R2D_COMPONENT_H_
