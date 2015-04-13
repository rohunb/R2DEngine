#ifndef R_CANNON_H_
#define R_CANNON_H_

#include "R2DScript.h"
#include "RInput.h"

namespace rb
{
	class Cannon : public R2DScript
	{
	public:
		Cannon() = default;
		Cannon(const Cannon& rhs) = delete;
		//Cannon(Cannon&& rhs);
		Cannon& operator = (const Cannon& rhs) = delete;
		//Cannon& operator = (Cannon&& rhs);
		~Cannon() = default;

		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void OnDestroy() override;
		virtual std::unique_ptr<R2DScript> Clone() const override;

	private:
		std::unique_ptr<GameObject> missilePrefab;
		float missileSpeed;
		std::shared_ptr<MouseClickEvent> onMouseClick;
		std::shared_ptr<KeyboardEvent> onKeyboard;
		void Fire(const Vec2& targetPos);
		void OnMouseClick(int button, int action, const Vec2& mousePos);
		void OnKeyboard(int key, int action);



	};
}

#endif // R_CANNON_H_
