#ifndef R_CANNON_H_
#define R_CANNON_H_

#include "R2DScript.h"

namespace rb
{
	class Cannon : public R2DScript
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;
		
	private:
		std::unique_ptr<GameObject> missilePrefab;
		float missileSpeed;

		void OnMouseClick(int button, int action, const Vec2& mousePos);
	};
}

#endif // R_CANNON_H_
