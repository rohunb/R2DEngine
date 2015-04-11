#ifndef R_GAME_SCENE_H_
#define R_GAME_SCENE_H_

#include "R2DScene.h"

namespace rb
{
	class GameScene : public R2DScene
	{
	public:
		virtual void Start() override;
		virtual void Update(float dt) override;

	private:
		std::unique_ptr<GameObject> asteroidPrefab;

		void OnMouseClick(int button, int action, const Vec2& mousePos);
	};
}

#endif // R_GAME_SCENE_H_
