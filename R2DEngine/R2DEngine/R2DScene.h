#ifndef R_R2D_SCENE_H_
#define R_R2D_SCENE_H_

#include <vector>
#include "GameObject.h"

namespace rb
{
	class R2DScene
	{
	public:
		R2DScene();
		R2DScene(const R2DScene& rhs);
		R2DScene(R2DScene&& rhs);
		R2DScene& operator = (const R2DScene& rhs);
		R2DScene& operator = ( R2DScene&& rhs);
		~R2DScene() = default;

		GameObject Instantiate(const GameObject& prefab);
		void Update(float dt);

	private:
		std::vector<std::shared_ptr<GameObject>> sceneObjects;
	};
}

#endif // R_R2D_SCENE_H_