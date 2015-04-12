
#ifndef R_SCENE_2_H_
#define R_SCENE_2_H_

#include "R2DScene.h"

namespace rb
{
	class Scene2 : public R2DScene
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;
		virtual void Exit() override;
	private:
		//prefabs
		std::unique_ptr<GameObject> missilePrefab;
	};
}
#endif // R_SCENE_2_H_


