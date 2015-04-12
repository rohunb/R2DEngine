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
		virtual void Exit() override;

	private:
		std::shared_ptr<MouseClickEvent> mouseClickEvent;
		std::unique_ptr<GameObject> asteroidSpawnerPrefab;
		std::unique_ptr<GameObject> cannonPrefab;

		void OnMouseClick(int button, int action, const Vec2& mousePos);


	};
}

#endif // R_GAME_SCENE_H_
