#ifndef R_CANNON_H_
#define R_CANNON_H_

#include "R2DScript.h"
#include "RInput.h"

namespace rb
{
	class Cannon : public R2DScript
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void OnDestroy() override;

	private:
		std::unique_ptr<GameObject> missilePrefab;
		float missileSpeed;
		std::shared_ptr<MouseClickEvent> onMouseClick;
		void OnMouseClick(int button, int action, const Vec2& mousePos);


	};
}

#endif // R_CANNON_H_
