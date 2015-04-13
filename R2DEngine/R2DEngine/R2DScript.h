#ifndef R_R2D_SCRIPT_H_
#define R_R2D_SCRIPT_H_

#include "R2DComponent.h"
#include <memory>
#include "GameObject.h"

namespace rb
{
	class R2DScript : public R2DComponent
	{
	public:
		R2DScript() = default;
		R2DScript(const R2DScript& rhs) = default;
		R2DScript(R2DScript&& rhs){};
		R2DScript& operator = (const R2DScript& rhs) = default;
		R2DScript& operator = (R2DScript&& rhs){};
		virtual ~R2DScript() = default;

		virtual void Start() ;
		virtual void Update(float dt) ;
		virtual void OnDestroy() ;
		virtual std::unique_ptr<R2DScript> Clone() const = 0;

		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab);
		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab, const Vec2& position, float rotation);
		void Destroy(std::shared_ptr<GameObject>& gameObject);

	private:
		std::shared_ptr<class R2DScene> currentScene;

		friend class R2DGame;
	};
}
#endif // R_R2D_SCRIPT_H_
