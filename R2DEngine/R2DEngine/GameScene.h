#ifndef R_GAME_SCENE_H_
#define R_GAME_SCENE_H_

#include "R2DScene.h"
#include "RInput.h"

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
		std::unique_ptr<GameObject> backgroundPrefab;
		std::unique_ptr<GameObject> city1Prefab;
		void OnMouseClick(int button, int action, const Vec2& mousePos);
	};
}

#endif // R_GAME_SCENE_H_
