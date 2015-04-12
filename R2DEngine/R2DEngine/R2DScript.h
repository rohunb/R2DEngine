#ifndef R_R2D_SCRIPT_H_
#define R_R2D_SCRIPT_H_

#include "R2DComponent.h"
#include <memory>
#include "RVector.h"
#include "RTime.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "RDebug.h"
#include "RRandom.h"
#include "Screen.h"
#include "RInput.h"

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

		virtual void Start() = 0;
		virtual void Update(float dt) = 0;
		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab);
		std::shared_ptr<GameObject> Instantiate(const GameObject& prefab, const Vec2& position, float rotation);

	private:
		std::shared_ptr<class R2DScene> currentScene;

		friend class R2DGame;
	};
}
#endif // R_R2D_SCRIPT_H_
