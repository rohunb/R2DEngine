#ifndef R_R2D_SCENE_H_
#define R_R2D_SCENE_H_

#include <vector>
#include <functional>
#include "GameObject.h"
#include "RVector.h"

namespace rb
{
	class R2DScene
	{
	public:
		R2DScene(std::function<void(GameObject&)> instantiateCallback);
		R2DScene(const R2DScene& rhs);
		R2DScene(R2DScene&& rhs);
		R2DScene& operator = (const R2DScene& rhs);
		R2DScene& operator = ( R2DScene&& rhs);
		~R2DScene() = default;

		GameObject Instantiate(const GameObject& prefab);
		GameObject Instantiate(const GameObject& prefab, const Vec2& position, float rotation);
		void Update(float dt);

	private:
		std::vector<std::shared_ptr<GameObject>> sceneObjects;
		std::shared_ptr<GameObject> missile;


		std::function<void(GameObject&)> instantiateCallback;
		friend class R2DGame;
	};
}

#endif // R_R2D_SCENE_H_