#include "GameScene.h"

void rb::GameScene::Start()
{
	asteroidPrefab = std::make_unique<GameObject>(TextureManager::GetTexture("Asteroid"));
	asteroidPrefab->SetTransform(Vec2(200.0f),0.0f);
	asteroidPrefab->GetTransform()->size *= 0.3f;

	Instantiate(*asteroidPrefab);
	BackgroundColour(Colour::blue);
}

void rb::GameScene::Update(float dt)
{
	
}
